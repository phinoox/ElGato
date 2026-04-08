// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/AttributeEditorFunctionLibrary.h"

#include "ContentBrowserModule.h"
#include "GaMaLog.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Attributes/GaMaBaseAttributeSet.h"
#include "Data/FMainAttributeData.h"
#include "UObject/SavePackage.h"
#include "Serialization/JsonSerializer.h"

TArray<FString> UAttributeEditorFunctionLibrary::GetScalableAttributes(UGaMaBaseAttributeSet* AttributeSet)
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

UDataTable* UAttributeEditorFunctionLibrary::CreateTableForAttributeSet(UGaMaBaseAttributeSet* AttributeSet,FName AssetName,bool OnlyCurves)
{
	FString ContentPathString = TEXT("/Game/Data/");
	ContentPathString = ContentPathString.Replace(TEXT("//"),TEXT("/"));
	ContentPathString.Append(AssetName.ToString());
	FString TableAssetName = "DT_Attributes_" + AssetName.ToString();
	auto TablePathString = ContentPathString + "/" + TableAssetName;
	//auto ContentPath = TablePathString.GetCharArray().GetData();
	auto ContentPath = FPackageName::LongPackageNameToFilename(TablePathString,FPackageName::GetAssetPackageExtension());
	UPackage* NewPackage = CreatePackage(*TablePathString);
	NewPackage->FullyLoad();	
		
	TArray<FString> ScalableAttributes = GetScalableAttributes(AttributeSet);
	UCurveTable* LevelCurves = CreateCurveTable(ScalableAttributes,AssetName);
	
	if (OnlyCurves)
		return nullptr;
	

	EObjectFlags Flags = RF_Public | RF_Standalone;
	UDataTable* NewTable = NewObject<UDataTable>(NewPackage,UDataTable::StaticClass(), FName(TableAssetName), Flags);
	
	NewTable->RowStruct = FLeveledAttributeData::StaticStruct();
	NewTable->CreateTableFromJSONString(CreateJsonForAttributeSet(AttributeSet));
	
	
	for (FName RowName : NewTable->GetRowNames())
	{
		FLeveledAttributeData* RowHandle = NewTable->FindRow<FLeveledAttributeData>(RowName, "");
		
		RowHandle->Value.CurveTable = LevelCurves;
		RowHandle->Value.RowName = RowName;
		 
	}
	
	
	
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone; // Flags for objects to save
	SaveArgs.SaveFlags = SAVE_None; // Flags to control saving behavior

	// Save the asset to disk
	NewTable->MarkPackageDirty();
	UE_LOG(LogGasMaster,Display,TEXT("Trying to save DataTable at %s"),*TablePathString);
	FAssetRegistryModule::AssetCreated(NewTable);
	bool success= UPackage::SavePackage(NewPackage,NewTable,*ContentPath,SaveArgs);
	UE_LOG(LogGasMaster,Display,TEXT("Save Curvtetable %s"),success ? TEXT("Successfull") : TEXT("Failed"));
	NewPackage->FullyLoad();
	NewPackage->Rename(*NewPackage->GetName());
	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	TArray<UObject*> NewTables;
	NewTables.Add(NewTable);
	NewTables.Add(LevelCurves);
	ContentBrowserModule.Get().SyncBrowserToAssets(NewTables);
	
	return NewTable;
}

FString UAttributeEditorFunctionLibrary::CreateJsonForAttributeSet(UGaMaBaseAttributeSet* AttributeSet)
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

UCurveTable* UAttributeEditorFunctionLibrary::CreateCurveTable(TArray<FString> AttributeNames,FName AssetName)
{
	FString ContentPathString = TEXT("/Game/Data/");
	ContentPathString = ContentPathString.Replace(TEXT("//"),TEXT("/"));
	ContentPathString.Append(AssetName.ToString());
	FString TableAssetName = "CT_AttributeLevels_" + AssetName.ToString();
	auto TablePathString = ContentPathString + "/" + TableAssetName;
	auto ContentPath = FPackageName::LongPackageNameToFilename(TablePathString,FPackageName::GetAssetPackageExtension());
	UPackage* NewPackage = CreatePackage(*TablePathString);
	NewPackage->FullyLoad();
	UCurveTable* NewTable = NewObject<UCurveTable>(NewPackage,UCurveTable::StaticClass(),FName(TableAssetName),RF_Public |RF_Standalone);
	for (auto AttributeName : AttributeNames)
	{
		auto curve = NewTable->AddSimpleCurve(FName(GetShortName(AttributeName)));
		curve.AddKey(1,1);
	}
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone; // Flags for objects to save
	SaveArgs.Error = GError;
	SaveArgs.SaveFlags = SAVE_KeepGUID ; // Flags to control saving behavior

	// Save the asset to disk
	NewTable->MarkPackageDirty();
	UE_LOG(LogGasMaster,Display,TEXT("Trying to save curvtetable at %s"),*TablePathString);
	FAssetRegistryModule::AssetCreated(NewTable);
	bool success = UPackage::SavePackage(NewPackage,NewTable,*ContentPath,SaveArgs);
	UE_LOG(LogGasMaster,Display,TEXT("Save Curvtetable %s"),success ? TEXT("Successfull") : TEXT("Failed"));
	NewPackage->Rename(*NewPackage->GetName());
	return NewTable;
}
