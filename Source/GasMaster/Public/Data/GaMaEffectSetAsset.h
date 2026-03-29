// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Base/GaMaGameplayEffectBase.h"
#include "GaMaEffectSetAsset.generated.h"


/**
 * A set of gameplay effects editable with data asssets
 */

USTRUCT(BlueprintType)
struct  GASMASTER_API FGaMaEffectData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet")
	TSubclassOf<UGaMaGameplayEffectBase> EffectClass;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet")
	FText DisplayName;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet")
	TObjectPtr<UTexture2D> Icon;
};



UCLASS()
class GASMASTER_API UGaMaEffectSetAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="AbilitySet",meta=(RowType="/Script/CorruptedCold.GaMaEffectData"))
	TArray<FDataTableRowHandle> Effects;
	
	UFUNCTION()
	FGaMaEffectData GetEffectAssetByName(FText Name);
	
	UFUNCTION()
	FGaMaEffectData GetEffectAssetByClass(TSubclassOf<UGaMaGameplayEffectBase> EffectClass);
	
};
