// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/DataAsset.h"
#include "GaToAbilitySetAsset.generated.h"

class UImage;

class UGaToGameplayAbilityBase;
/**
 * 
 */


USTRUCT(BlueprintType)
struct ElGaTo_API FGaToAbilityData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet")
	TSubclassOf<UGaToGameplayAbilityBase> AbilityClass;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet")
	FText DisplayName;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet")
	TObjectPtr<UTexture2D> Icon;
	
};

UCLASS(BlueprintType)
class ElGaTo_API UGaToAbilitySetAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet",meta=(RowType="/Script/ElGaTo.GaToAbilityData"))
	TArray<FDataTableRowHandle> Abilities;
	
	UFUNCTION()
	FGaToAbilityData GetAbilityAssetByName(FText Name);
	
	UFUNCTION()
	FGaToAbilityData GetAbilityAssetByClass(TSubclassOf<UGaToGameplayAbilityBase> AbilityClass);
	
};
