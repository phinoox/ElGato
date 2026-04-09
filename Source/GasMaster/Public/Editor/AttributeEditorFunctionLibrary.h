// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AttributeEditorFunctionLibrary.generated.h"

class UGaToBaseAttributeSet;
/**
 * 
 */
UCLASS()
class ElGaTo_API UAttributeEditorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,CallInEditor)
	static TArray<FString> GetScalableAttributes(UGaToBaseAttributeSet* AttributeSet);
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	static UDataTable* CreateTableForAttributeSet(UGaToBaseAttributeSet* AttributeSet,FName AssetName,bool OnlyCurves=false);
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	static FString CreateJsonForAttributeSet(UGaToBaseAttributeSet* AttributeSet);
	
	static FString GetShortName(const FString& AttributeName);
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	static UCurveTable* CreateCurveTable(TArray<FString> AttributeNames,FName AssetName);
	
};
