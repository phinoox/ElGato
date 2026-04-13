// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/AbilityEditorSubsystem.h"

#include "ElGaToConfig.h"
#include "ElGaToSettings.h"
#include "Data/GaToAbilitySetAsset.h"
#include "Data/GaToEffectSetAsset.h"
#include "Editor/AbilityAssetEditorFunctionLibrary.h"
#include "Internationalization/StringTable.h"

void UAbilityEditorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UAbilityEditorSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

TObjectPtr<UDataTable> UAbilityEditorSubsystem::GetAbilityTable()
{
	static const UElGaToSettings* Settings = GetDefault<UElGaToSettings>();
	static FString AssetPath = Settings->AssetBasePath.Path + "/" + GATOCONFIG::DEFAULT_ASSET_PATH + GATOCONFIG::DT_ABILITIES_NAME;

	if (UDataTable* LoadedTable = LoadObject<UDataTable>(GetTransientPackage(), AssetPath)) {
		return  LoadedTable;
	}
	else
	{
		UDataTable* AbilityTable = UAbilityAssetEditorFunctionLibrary::CreateDataTable(AssetPath, FString(GATOCONFIG::DT_ABILITIES_NAME),FGaToAbilityData::StaticStruct());
			
		return AbilityTable;
	}

}

TObjectPtr<UDataTable> UAbilityEditorSubsystem::GetEffectTable()
{
	static const UElGaToSettings* Settings = GetDefault<UElGaToSettings>();
	static FString AssetPath = Settings->AssetBasePath.Path + "/" + GATOCONFIG::DEFAULT_ASSET_PATH + GATOCONFIG::DT_EFFECTS_NAME;

	if (UDataTable* LoadedTable = LoadObject<UDataTable>(GetTransientPackage(), AssetPath)) {
		return  LoadedTable;
	}
	else
	{
		UDataTable* EffectTable = UAbilityAssetEditorFunctionLibrary::CreateDataTable(AssetPath, FString(GATOCONFIG::DT_EFFECTS_NAME),FGaToEffectData::StaticStruct());
		return EffectTable;
	}
}

TObjectPtr<UStringTable> UAbilityEditorSubsystem::GetAbilityStringTable()
{
	static const UElGaToSettings* Settings = GetDefault<UElGaToSettings>();
	static FString AssetPath = Settings->AssetBasePath.Path + "/" + GATOCONFIG::DEFAULT_ASSET_PATH + GATOCONFIG::ST_ABILITIES_NAME;

	if (UStringTable* LoadedTable = LoadObject<UStringTable>(GetTransientPackage(), AssetPath)) {
		return  LoadedTable;
	}
	else
	{
		UStringTable* EffectTable = UAbilityAssetEditorFunctionLibrary::CreateStringTable(AssetPath, FString(GATOCONFIG::ST_ABILITIES_NAME));
		return EffectTable;
	}
}

TObjectPtr<UStringTable> UAbilityEditorSubsystem::GetEffectStringTable()
{
	static const UElGaToSettings* Settings = GetDefault<UElGaToSettings>();
	static FString AssetPath = Settings->AssetBasePath.Path + "/" + GATOCONFIG::DEFAULT_ASSET_PATH + GATOCONFIG::ST_EFFECTS_NAME;

	if (UStringTable* LoadedTable = LoadObject<UStringTable>(GetTransientPackage(), AssetPath)) {
		return  LoadedTable;
	}
	else
	{
		UStringTable* EffectTable = UAbilityAssetEditorFunctionLibrary::CreateStringTable(AssetPath, FString(GATOCONFIG::ST_EFFECTS_NAME));
		return EffectTable;
	}
}
