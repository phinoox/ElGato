// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AttributeEditorFunctionLibrary.generated.h"

class UGaMaBaseAttributeSet;
/**
 * 
 */
UCLASS()
class GASMASTER_API UAttributeEditorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable,CallInEditor)
	static TArray<FString> GetScalableAttributes(UGaMaBaseAttributeSet* AttributeSet);
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	static UDataTable* CreateTableForAttributeSet(UGaMaBaseAttributeSet* AttributeSet,FName AssetName,bool OnlyCurves=false);
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	static FString CreateJsonForAttributeSet(UGaMaBaseAttributeSet* AttributeSet);
	
	static FString GetShortName(const FString& AttributeName);
	
	UFUNCTION(BlueprintCallable,CallInEditor)
	static UCurveTable* CreateCurveTable(TArray<FString> AttributeNames,FName AssetName);
	
};
