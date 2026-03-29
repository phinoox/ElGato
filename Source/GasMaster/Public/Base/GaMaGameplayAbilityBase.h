// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GaMaGameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GASMASTER_API UGaMaGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="AbilityAsset",meta=(RowType="/Script/CorruptedCold.GaMaAbilityData"))
	TObjectPtr<UDataTable> AbilityTable;
	
	UFUNCTION(BlueprintCallable)
	FName GetAbilityName() const;
#if WITH_EDITOR
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	
private:
	UFUNCTION(BlueprintCallable,CallInEditor)
	void AddToTable();
		
	
	
#endif
	
};
