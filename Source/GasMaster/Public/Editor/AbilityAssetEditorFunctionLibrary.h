// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AbilityAssetEditorFunctionLibrary.generated.h"

class UGaToEffectSetAsset;
class UGaToAbilitySetAsset;

USTRUCT()
struct FAssetPathInfo
{
	GENERATED_BODY()
public:
	FAssetPathInfo(){};
	FAssetPathInfo(FString CharacterName);
	
	FString CharacterName;
	/*Short path to the asset directory*/
	FString AssetPath;
	/* Long Path to the asset directory needed when saving */
	FString LongAssetPath;
};


class UGaToBaseAttributeSet;
/**
 * 
 */
UCLASS()
class ELGATO_API UAbilityAssetEditorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,CallInEditor)
	static TArray<FString> GetScalableAttributes(UGaToBaseAttributeSet* AttributeSet);
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	static UDataTable* CreateTableForAttributeSet(UGaToBaseAttributeSet* AttributeSet,FName CharacterName);
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	static FString CreateJsonForAttributeSet(UGaToBaseAttributeSet* AttributeSet);
	
	static FString GetShortName(const FString& AttributeName);
	
	UFUNCTION()
	static UCurveTable* CreateCurveTable(TArray<FString> AttributeNames,const FAssetPathInfo& AssetPathInfo,const FName AssetName);
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	static void CreateGameplayAsset(TScriptInterface<IGaToActorInterface> Actor, FName CharacterName);
	
	static UGaToAbilitySetAsset* CreateAbilitySetAsset(const FAssetPathInfo& AssetPathInfo, const FString& AssetName);
	
	static UGaToEffectSetAsset* CreateEffectSetAsset(const FAssetPathInfo& AssetPathInfo, const FString& AssetName);
	
	
	static UPackage* CreateNewPackage(const FAssetPathInfo& AssetPathInfo, const FString& AssetName);
	
	static UPackage* CreateNewPackage(const FString& AssetPath,FString AssetName);
	
	static void SaveNewPackage(UPackage* Package,UObject* NewAsset,const FAssetPathInfo& AssetPathInfo, const FString& AssetName);
	
	static void SaveNewPackage(UPackage* Package,UObject* NewAsset,const FString& AssetPath,FString AssetName);
	
	UFUNCTION()
	static UDataTable* CreateDataTable(const FString& Path, const FString& AssetName,UScriptStruct* RowStruct);
	
	UFUNCTION()
	static UStringTable* CreateStringTable(const FString& Path, const FString& AssetName);
	
	UFUNCTION()
	static bool SaveAsset(UObject* ObjectToSave);
};
