// Fill out your copyright notice in the Description page of Project Settings.


#include "Editor/AbilityEditorSubsystem.h"

#include "ElGaToConfig.h"
#include "ElGaToSettings.h"
#include "Editor/AbilityAssetEditorFunctionLibrary.h"

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
		UDataTable* AbilityTable = UAbilityAssetEditorFunctionLibrary::CreateAbilityTable(AssetPath, FString(GATOCONFIG::DT_ABILITIES_NAME));
			
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
		UDataTable* EffectTable = UAbilityAssetEditorFunctionLibrary::CreateEffectTable(AssetPath, FString(GATOCONFIG::DT_EFFECTS_NAME));
		return EffectTable;
	}
}
