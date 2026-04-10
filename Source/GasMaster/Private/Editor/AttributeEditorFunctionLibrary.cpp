// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/AttributeEditorFunctionLibrary.h"

#include "ContentBrowserModule.h"
#include "GaToLog.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Attributes/GaToBaseAttributeSet.h"
#include "Data/FLeveledAttributeData.h"
#include "UObject/SavePackage.h"
#include "Serialization/JsonSerializer.h"

FAssetPathInfo::FAssetPathInfo(FString CharacterName)
{
	static FString ContentPath = TEXT("/Game/Data/");
	
	this->CharacterName = CharacterName;
	this->AssetPath = ContentPath + CharacterName + "/";
	this->LongAssetPath = FPackageName::LongPackageNameToFilename(AssetPath);
	
}

TArray<FString> UAttributeEditorFunctionLibrary::GetScalableAttributes(UGaToBaseAttributeSet* AttributeSet)
{
	TArray<FString> ScalableAttributes;
	
	for (TFieldIterator<FProperty> PropIt(AttributeSet->GetClass()); PropIt; ++PropIt)
	{
		FProperty* Property = *PropIt;
		const FStructProperty* StructProp = CastField<FStructProperty>(Property);
		//StructProp->Struct
		if ( StructProp && StructProp->Struct == FGameplayAttributeData::StaticStruct() && Property->HasMetaData(TEXT("InitialValue")))
		{
			FString Name =Property->GetFullName();
			Name.RemoveFromStart("StructProperty");
			Name = Name.TrimStart();
			ScalableAttributes.Add(Name);
		}
		
		// Do something with the property
	}
	
	return ScalableAttributes;
}

UDataTable* UAttributeEditorFunctionLibrary::CreateTableForAttributeSet(UGaToBaseAttributeSet* AttributeSet,FName CharacterName,bool OnlyCurves)
{
	if (AttributeSet == nullptr)
		return nullptr;
	FString TableAssetName = "DT_Attributes_" + CharacterName.ToString();
	
	FAssetPathInfo AssetPathInfo(CharacterName.ToString());
	
	TArray<FString> ScalableAttributes = GetScalableAttributes(AttributeSet);
	UCurveTable* LevelCurves = CreateCurveTable(ScalableAttributes,AssetPathInfo,CharacterName);
	
	if (OnlyCurves)
		return nullptr;
	
	auto Package = CreateNewPackage(AssetPathInfo,TableAssetName);
	UDataTable* NewTable = NewObject<UDataTable>(Package,UDataTable::StaticClass(), FName(TableAssetName), RF_Public |RF_Standalone);
	
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
	SaveNewPackage(Package,NewTable,AssetPathInfo,TableAssetName);
	
	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	
	TArray<UObject*> NewTables;
	NewTables.Add(NewTable);
	NewTables.Add(LevelCurves);
	ContentBrowserModule.Get().SyncBrowserToAssets(NewTables);
	
	return NewTable;
}

FString UAttributeEditorFunctionLibrary::CreateJsonForAttributeSet(UGaToBaseAttributeSet* AttributeSet)
{
	TArray<FString> ScalableAttributes = GetScalableAttributes(AttributeSet);
	const FString AttributeTemplate ="(AttributeName=\"ShortName\",Attribute=FullName,AttributeOwner=None)";
	const FString CurveTableTemplate ="(CurveTable=\"/Script/Engine.CurveTable'TablePath'\",RowName=\"ShortName\")";
	
	TArray<TSharedPtr<FJsonValue>> PropertiesList;
	for (auto AttributeName : ScalableAttributes)
	{
		TSharedRef<FJsonObject> ChildObject = MakeShareable(new FJsonObject());
        FString ShortName = GetShortName(AttributeName);
		
		FString AttributeString = AttributeTemplate;
		AttributeString = AttributeString.Replace(TEXT("ShortName"),*ShortName);
		AttributeString = AttributeString.Replace(TEXT("FullName"),*AttributeName);
		
		FString CurveString = CurveTableTemplate;
		CurveString = CurveString.Replace(TEXT("ShortName"),*ShortName);
		CurveString =  CurveString.Replace(TEXT("TablePath"),*ShortName);
		// Populate child fields
		ChildObject->SetStringField("Name", ShortName);
		ChildObject->SetStringField("Attribute", AttributeString);
		ChildObject->SetStringField("Value", CurveTableTemplate);
		ChildObject->SetNumberField("FallbackValue",0);

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

FString UAttributeEditorFunctionLibrary::GetShortName(const FString& AttributeName)
{
	FString ShortName;
	AttributeName.Split(":",nullptr,&ShortName);
	return ShortName;
}

UCurveTable* UAttributeEditorFunctionLibrary::CreateCurveTable(TArray<FString> AttributeNames,FAssetPathInfo AssetPathInfo,const FName AssetName)
{
	FString TableAssetName = "CT_AttributeLevels_" + AssetName.ToString();
	//need to create package upfront so we can set it as outer else we crash 
	auto Package = CreateNewPackage(AssetPathInfo,TableAssetName);
	UCurveTable* NewTable = NewObject<UCurveTable>(Package,UCurveTable::StaticClass(),FName(TableAssetName),RF_Public |RF_Standalone);
	NewTable->Modify();
	for (auto AttributeName : AttributeNames)
	{
		FSimpleCurve curve = NewTable->AddSimpleCurve(FName(GetShortName(AttributeName)));
		
	}
	float NewKeyTime = 1;
	for (const TPair<FName, FRealCurve*>& CurveRow : NewTable->GetRowMap())
	{
		FRealCurve* Curve = CurveRow.Value;
		Curve->UpdateOrAddKey(NewKeyTime, Curve->Eval(NewKeyTime,1));
	}

	// Save the asset to disk
	NewTable->MarkPackageDirty();
	SaveNewPackage(Package,NewTable,AssetPathInfo,TableAssetName);
	return NewTable;
}

void UAttributeEditorFunctionLibrary::CreateGameplayAsset(FName AssetName)
{
//	auto GamePlayAsset = NewObject
}

UPackage* UAttributeEditorFunctionLibrary::CreateNewPackage(FAssetPathInfo AssetPathInfo,FString AssetName)
{
	auto ShortPackagePath = AssetPathInfo.AssetPath + AssetName;
	
	UPackage* NewPackage = CreatePackage(*ShortPackagePath);
	NewPackage->FullyLoad();

	return NewPackage;	
}

void UAttributeEditorFunctionLibrary::SaveNewPackage(UPackage* Package, UObject* NewAsset,FAssetPathInfo AssetPathInfo, FString AssetName)
{
	auto NewAssetPath = AssetPathInfo.AssetPath + AssetName;
	
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone; // Flags for objects to save
	SaveArgs.Error = GError;
	SaveArgs.SaveFlags = SAVE_KeepGUID;

	auto ContentPath = FPackageName::LongPackageNameToFilename(NewAssetPath,FPackageName::GetAssetPackageExtension());
	FAssetRegistryModule::AssetCreated(NewAsset);
	bool success = UPackage::SavePackage(Package,NewAsset,*ContentPath,SaveArgs);
	UE_LOG(LogGaTo,Display,TEXT("Save Curvtetable %s"),success ? TEXT("Successfull") : TEXT("Failed"));
}
