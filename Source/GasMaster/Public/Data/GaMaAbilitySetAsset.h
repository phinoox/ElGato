// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/DataAsset.h"
#include "GaMaAbilitySetAsset.generated.h"

class UImage;

class UGaMaGameplayAbilityBase;
/**
 * 
 */


USTRUCT(BlueprintType)
struct GASMASTER_API FGaMaAbilityData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet")
	TSubclassOf<UGaMaGameplayAbilityBase> AbilityClass;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet")
	FText DisplayName;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet")
	TObjectPtr<UTexture2D> Icon;
	
};

UCLASS(BlueprintType)
class GASMASTER_API UGaMaAbilitySetAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet",meta=(RowType="/Script/CorruptedCold.GaMaAbilityData"))
	TArray<FDataTableRowHandle> Abilities;
	
	UFUNCTION()
	FGaMaAbilityData GetAbilityAssetByName(FText Name);
	
	UFUNCTION()
	FGaMaAbilityData GetAbilityAssetByClass(TSubclassOf<UGaMaGameplayAbilityBase> AbilityClass);
	
};
