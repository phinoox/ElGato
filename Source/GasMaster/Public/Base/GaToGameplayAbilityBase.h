// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GaToGameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ELGATO_API UGaToGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UGaToGameplayAbilityBase();
	
public:
	
	
public:
	UFUNCTION(BlueprintCallable)
	FName GetAbilityName() const;
#if WITH_EDITOR
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	
private:
	UFUNCTION()
	void AddToTable();
	
#endif
	
};
