// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Base/GaToGameplayEffectBase.h"
#include "GaToEffectSetAsset.generated.h"


/**
 * A set of gameplay effects editable with data asssets
 */

USTRUCT(BlueprintType)
struct  ELGATO_API FGaToEffectData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet")
	TSubclassOf<UGaToGameplayEffectBase> EffectClass;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet")
	FText DisplayName;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet")
	TObjectPtr<UTexture2D> Icon;
};



UCLASS(BlueprintType)
class ELGATO_API UGaToEffectSetAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet",meta=(RowType="/Script/ElGaTo.GaToEffectData"))
	TArray<FDataTableRowHandle> Effects;
	
	UFUNCTION()
	FGaToEffectData GetEffectAssetByName(FText Name);
	
	UFUNCTION()
	FGaToEffectData GetEffectAssetByClass(TSubclassOf<UGaToGameplayEffectBase> EffectClass);
	
};
