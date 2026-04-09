// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GaToGameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ElGaTo_API UGaToGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UGaToGameplayAbilityBase();
	
public:
	
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="AbilityAsset",meta=(RowType="/Script/ElGaTo.GaToAbilityData"))
	TObjectPtr<UDataTable> AbilityTable;
	
	UFUNCTION(BlueprintCallable)
	FName GetAbilityName() const;
#if WITH_EDITOR
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	
private:
	UFUNCTION()
	void AddToTable();
	
#endif
	
};
