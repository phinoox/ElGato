// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AttributeEditorFunctionLibrary.generated.h"

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
class ELGATO_API UAttributeEditorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,CallInEditor)
	static TArray<FString> GetScalableAttributes(UGaToBaseAttributeSet* AttributeSet);
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	static UDataTable* CreateTableForAttributeSet(UGaToBaseAttributeSet* AttributeSet,FName CharacterName,bool OnlyCurves=false);
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	static FString CreateJsonForAttributeSet(UGaToBaseAttributeSet* AttributeSet);
	
	static FString GetShortName(const FString& AttributeName);
	
	UFUNCTION()
	static UCurveTable* CreateCurveTable(TArray<FString> AttributeNames,FAssetPathInfo AssetPathInfo,const FName AssetName);
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	static void CreateGameplayAsset(FName AssetName);
	
	UFUNCTION()
	static UPackage* CreateNewPackage(FAssetPathInfo AssetPathInfo,FString AssetName);
	
	UFUNCTION()
	static void SaveNewPackage(UPackage* Package,UObject* NewAsset,FAssetPathInfo AssetPathInfo,FString AssetName);
	
};
