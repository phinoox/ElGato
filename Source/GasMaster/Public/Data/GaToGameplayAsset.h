// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GaToAbilitySetAsset.h"
#include "GaToEffectSetAsset.h"
#include "Base/GaToGameplayEffectBase.h"
#include "Base/GaToGameplayAbilityBase.h"
#include "GaToGameplayAsset.generated.h"

/**
 * 
 */
UCLASS()
class ELGATO_API UGaToGameplayAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	TArray<TObjectPtr<UGaToAbilitySetAsset>> AbilitySets;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	TObjectPtr<UGaToEffectSetAsset> InitialEffects;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	TObjectPtr<UGaToAbilitySetAsset> ReactiveAbilities;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	FGameplayTagContainer InitialTags;
		
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	TObjectPtr<UDataTable> AttributeTable;
	
	

};
