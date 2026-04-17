// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/AbilityAssetEditorFunctionLibrary.h"

#include "ContentBrowserModule.h"
#include "ElGaToConfig.h"
#include "ElGaToSettings.h"
#include "GaToLog.h"
#include "IContentBrowserSingleton.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Attributes/GaToBaseAttributeSet.h"
#include "Base/GaToActorInterface.h"
#include "Components/GaToGamePlayAssetComponent.h"
#include "Data/FLeveledAttributeData.h"
#include "Data/GaToGameplayAsset.h"
#include "Internationalization/StringTable.h"
#include "Serialization/JsonSerializer.h"
#include "UObject/SavePackage.h"

FAssetPathInfo::FAssetPathInfo(FString CharacterName)
{
	static const UElGaToSettings* Settings = GetDefault<UElGaToSettings>();
	static FString ContentPath = Settings->AssetBasePath.Path + "/";
	this->CharacterName = CharacterName;
	this->AssetPath = ContentPath + CharacterName + "/";
	this->LongAssetPath = FPackageName::LongPackageNameToFilename(AssetPath);
}

TArray<FString> UAbilityAssetEditorFunctionLibrary::GetScalableAttributes(UGaToBaseAttributeSet* AttributeSet)
{
	TArray<FString> ScalableAttributes;

	for (TFieldIterator<FProperty> PropIt(AttributeSet->GetClass()); PropIt; ++PropIt)
	{
		FProperty* Property = *PropIt;
		const FStructProperty* StructProp = CastField<FStructProperty>(Property);
		//StructProp->Struct
		if (StructProp && StructProp->Struct == FGameplayAttributeData::StaticStruct() && Property->HasMetaData(
			TEXT("InitialValue")))
		{
			FString Name = Property->GetFullName();
			Name.RemoveFromStart("StructProperty");
			Name = Name.TrimStart();
			ScalableAttributes.Add(Name);
		}
	}

	return ScalableAttributes;
}

UDataTable* UAbilityAssetEditorFunctionLibrary::CreateTableForAttributeSet(
	UGaToBaseAttributeSet* AttributeSet, FName CharacterName)
{
	if (AttributeSet == nullptr)
	{
		return nullptr;
	}
	FString TableAssetName = GATOCONFIG::DT_ATTRIBUTS_PREFIX + CharacterName.ToString();

	FAssetPathInfo AssetPathInfo(CharacterName.ToString());

	TArray<FString> ScalableAttributes = GetScalableAttributes(AttributeSet);
	UCurveTable* LevelCurves = CreateCurveTable(ScalableAttributes, AssetPathInfo, CharacterName);


	UPackage* Package = CreateNewPackage(AssetPathInfo, TableAssetName);
	UDataTable* NewTable = NewObject<UDataTable>(Package, UDataTable::StaticClass(), FName(TableAssetName),
	                                             RF_Public | RF_Standalone);

	NewTable->RowStruct = FLeveledAttributeData::StaticStruct();
	NewTable->CreateTableFromJSONString(CreateJsonForAttributeSet(AttributeSet));


	for (FName RowName : NewTable->GetRowNames())
	{
		FLeveledAttributeData* RowHandle = NewTable->FindRow<FLeveledAttributeData>(RowName, "");

		RowHandle->Value.CurveTable = LevelCurves;
		RowHandle->Value.RowName = RowName;
	}

	// Save the asset to disk
	NewTable->MarkPackageDirty();
	SaveNewPackage(Package, NewTable, AssetPathInfo, TableAssetName);

	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(
		"ContentBrowser");

	TArray<UObject*> NewTables;
	NewTables.Add(NewTable);
	NewTables.Add(LevelCurves);
	ContentBrowserModule.Get().SyncBrowserToAssets(NewTables);

	return NewTable;
}

FString UAbilityAssetEditorFunctionLibrary::CreateJsonForAttributeSet(UGaToBaseAttributeSet* AttributeSet)
{
	TArray<FString> ScalableAttributes = GetScalableAttributes(AttributeSet);
	const FString AttributeTemplate = "(AttributeName=\"ShortName\",Attribute=FullName,AttributeOwner=None)";
	const FString CurveTableTemplate = "(CurveTable=\"/Script/Engine.CurveTable'TablePath'\",RowName=\"ShortName\")";

	TArray<TSharedPtr<FJsonValue>> PropertiesList;
	for (FString AttributeName : ScalableAttributes)
	{
		TSharedRef<FJsonObject> ChildObject = MakeShareable(new FJsonObject());
		FString ShortName = GetShortName(AttributeName);

		FString AttributeString = AttributeTemplate;
		AttributeString = AttributeString.Replace(TEXT("ShortName"), *ShortName);
		AttributeString = AttributeString.Replace(TEXT("FullName"), *AttributeName);

		FString CurveString = CurveTableTemplate;
		CurveString = CurveString.Replace(TEXT("ShortName"), *ShortName);
		CurveString = CurveString.Replace(TEXT("TablePath"), *ShortName);
		// Populate child fields
		ChildObject->SetStringField("Name", ShortName);
		ChildObject->SetStringField("Attribute", AttributeString);
		ChildObject->SetStringField("Value", CurveTableTemplate);
		ChildObject->SetNumberField("FallbackValue", 0);

		// Add child to the array
		PropertiesList.Add(MakeShareable(new FJsonValueObject(ChildObject)));
		// 4. Add the array to the outer object
	}

	// 5. Serialize to string
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(PropertiesList, Writer);
	Writer->Close();

	return OutputString;
}

FString UAbilityAssetEditorFunctionLibrary::GetShortName(const FString& AttributeName)
{
	FString ShortName;
	AttributeName.Split(":", nullptr, &ShortName);
	return ShortName;
}

UCurveTable* UAbilityAssetEditorFunctionLibrary::CreateCurveTable(TArray<FString> AttributeNames,
                                                                  const FAssetPathInfo& AssetPathInfo,
                                                                  const FName AssetName)
{
	FString TableAssetName = GATOCONFIG::CT_ATTRIBUTELEVELS_PREFIX + AssetName.ToString();
	//need to create package upfront so we can set it as outer else we crash 
	UPackage* Package = CreateNewPackage(AssetPathInfo, TableAssetName);
	//remember to create the object with a proper unique name else it won't show up in the content browser
	UCurveTable* NewTable = NewObject<UCurveTable>(Package, UCurveTable::StaticClass(), FName(TableAssetName),
	                                               RF_Public | RF_Standalone);
	NewTable->Modify();
	for (FString AttributeName : AttributeNames)
	{
		FSimpleCurve curve = NewTable->AddSimpleCurve(FName(GetShortName(AttributeName)));
	}
	// code stolen from Source/Editor/CurveTableEditor/Private/CurveTableEditor.cpp
	for (const TPair<FName, FRealCurve*>& CurveRow : NewTable->GetRowMap())
	{
		float NewKeyTime = 1;
		FRealCurve* Curve = CurveRow.Value;
		Curve->UpdateOrAddKey(NewKeyTime, Curve->Eval(NewKeyTime, 1));
	}

	// Save the asset to disk
	NewTable->MarkPackageDirty();
	SaveNewPackage(Package, NewTable, AssetPathInfo, TableAssetName);
	return NewTable;
}

void UAbilityAssetEditorFunctionLibrary::CreateGameplayAsset(TScriptInterface<IGaToActorInterface>  Actor, FName CharacterName)
{
	
	auto AttributeSet = Actor->GetGaToMainAttributeSet();
	FString TableAssetName = GATOCONFIG::DA_GAMEPLAY_PREFIX + CharacterName.ToString();
	FAssetPathInfo AssetPathInfo(CharacterName.ToString());
	UPackage* Package = CreateNewPackage(AssetPathInfo, TableAssetName);
	TObjectPtr<UGaToGameplayAsset> GamePlayAsset = NewObject<UGaToGameplayAsset>(Package, UGaToGameplayAsset::StaticClass(),
	                                                                  FName(TableAssetName), RF_Public | RF_Standalone);
	GamePlayAsset->AbilitySets.Add(CreateAbilitySetAsset(AssetPathInfo,CharacterName.ToString()));
	GamePlayAsset->ReactiveAbilities = CreateAbilitySetAsset(AssetPathInfo,CharacterName.ToString());
	GamePlayAsset->InitialEffects = CreateEffectSetAsset(AssetPathInfo,CharacterName.ToString());
	GamePlayAsset->AttributeTable = CreateTableForAttributeSet(AttributeSet,CharacterName);
	
	GamePlayAsset->MarkPackageDirty();
	SaveNewPackage(Package, GamePlayAsset, AssetPathInfo, TableAssetName);
	
	Actor->GetGaToGamePlayAssetComponent()->GameplayAssetRef = GamePlayAsset;
	

	
}

UGaToAbilitySetAsset* UAbilityAssetEditorFunctionLibrary::CreateAbilitySetAsset( const FAssetPathInfo& AssetPathInfo, const FString& AssetName)
{
	FString TableAssetName = GATOCONFIG::DA_ABILITYSET_PREFIX + AssetName;
	UPackage* NewPackage = CreateNewPackage(AssetPathInfo,TableAssetName);
	NewPackage->FullyLoad();
	
	UGaToAbilitySetAsset* NewSetAsset = NewObject<UGaToAbilitySetAsset>(NewPackage, UGaToAbilitySetAsset::StaticClass(), FName(TableAssetName),
												 RF_Public | RF_Standalone);


	NewSetAsset->MarkPackageDirty();
	SaveNewPackage(NewPackage, NewSetAsset, AssetPathInfo, TableAssetName);

	return NewSetAsset;
}

UGaToEffectSetAsset* UAbilityAssetEditorFunctionLibrary::CreateEffectSetAsset( const FAssetPathInfo& AssetPathInfo,
	const FString& AssetName)
{
	FString TableAssetName = GATOCONFIG::DA_EFFECTSET_PREFIX + AssetName;
	UPackage* NewPackage = CreateNewPackage(AssetPathInfo,TableAssetName);
	NewPackage->FullyLoad();
	
	UGaToEffectSetAsset* NewSetAsset = NewObject<UGaToEffectSetAsset>(NewPackage, UGaToEffectSetAsset::StaticClass(), FName(TableAssetName),
												 RF_Public | RF_Standalone);


	NewSetAsset->MarkPackageDirty();
	SaveNewPackage(NewPackage, NewSetAsset, AssetPathInfo, TableAssetName);

	return NewSetAsset;
}

UPackage* UAbilityAssetEditorFunctionLibrary::CreateNewPackage(const FAssetPathInfo& AssetPathInfo, const FString& AssetName)
{
	FString ShortPackagePath = AssetPathInfo.AssetPath + AssetName;
	return CreateNewPackage(ShortPackagePath, AssetName);
}

UPackage* UAbilityAssetEditorFunctionLibrary::CreateNewPackage(const FString& AssetPath, FString AssetName)
{
	UPackage* NewPackage = CreatePackage(*AssetPath);
	NewPackage->FullyLoad();

	return NewPackage;
}

void UAbilityAssetEditorFunctionLibrary::SaveNewPackage(UPackage* Package, UObject* NewAsset,
                                                        const FAssetPathInfo& AssetPathInfo, const FString& AssetName)
{
	FString NewAssetPath = AssetPathInfo.AssetPath + AssetName;
	SaveNewPackage(Package, NewAsset, NewAssetPath, AssetName);
}

void UAbilityAssetEditorFunctionLibrary::SaveNewPackage(UPackage* Package, UObject* NewAsset, const FString& AssetPath,
                                                        FString AssetName)
{
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone; // Flags for objects to save
	SaveArgs.Error = GError;
	SaveArgs.SaveFlags = SAVE_NoError;

	FString ContentPath = FPackageName::LongPackageNameToFilename(AssetPath,
	                                                              FPackageName::GetAssetPackageExtension());
	FAssetRegistryModule::AssetCreated(NewAsset);
	bool success = UPackage::SavePackage(Package, NewAsset, *ContentPath, SaveArgs);
	UE_LOG(LogGaTo, Display, TEXT("Save Curvtetable %s"), success ? TEXT("Successfull") : TEXT("Failed"));
}

UDataTable* UAbilityAssetEditorFunctionLibrary::CreateDataTable(const FString& Path, const FString& AssetName,UScriptStruct* RowStruct)
{
	UPackage* NewPackage = CreatePackage(*Path);
	NewPackage->FullyLoad();

	UDataTable* NewTable = NewObject<UDataTable>(NewPackage, UDataTable::StaticClass(), FName(AssetName),
												 RF_Public | RF_Standalone);

	NewTable->RowStruct = RowStruct;

	NewTable->MarkPackageDirty();
	SaveNewPackage(NewPackage, NewTable, Path, AssetName);

	return NewTable;
}

UStringTable* UAbilityAssetEditorFunctionLibrary::CreateStringTable(const FString& Path, const FString& AssetName)
{
	UPackage* NewPackage = CreatePackage(*Path);
	NewPackage->FullyLoad();

	UStringTable* NewTable = NewObject<UStringTable>(NewPackage, UStringTable::StaticClass(), FName(AssetName),
												 RF_Public | RF_Standalone);

	NewTable->MarkPackageDirty();
	SaveNewPackage(NewPackage, NewTable, Path, AssetName);

	return NewTable;
}

bool UAbilityAssetEditorFunctionLibrary::SaveAsset(UObject* ObjectToSave)
{
	UPackage* Package = ObjectToSave->GetPackage();
	const FString PackageName = Package->GetName();
	const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	SaveArgs.SaveFlags = SAVE_NoError | SAVE_KeepDirty; // Keeps the asset dirty for editor prompts

	const bool bSucceeded = UPackage::SavePackage(Package, nullptr, *PackageFileName, SaveArgs);

	if (!bSucceeded)
	{
		UE_LOG(LogTemp, Error, TEXT("Package '%s' wasn't saved!"), *PackageName);
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Package '%s' was successfully saved"), *PackageName);
	return true;
}
