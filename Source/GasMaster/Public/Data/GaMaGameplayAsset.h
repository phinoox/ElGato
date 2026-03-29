// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GaMaAbilitySetAsset.h"
#include "GaMaEffectSetAsset.h"
#include "Base/GaMaGameplayEffectBase.h"
#include "Base/GaMaGameplayAbilityBase.h"
#include "GaMaGameplayAsset.generated.h"

/**
 * 
 */
UCLASS()
class GASMASTER_API UGaMaGameplayAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	TArray<TObjectPtr<UGaMaAbilitySetAsset>> AbilitySets;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	TObjectPtr<UGaMaEffectSetAsset> InitialEffects;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	TObjectPtr<UGaMaAbilitySetAsset> ReactiveAbilities;
	

};
