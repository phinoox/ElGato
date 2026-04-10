// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GaToGameplayEffectBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ELGATO_API UGaToGameplayEffectBase : public UGameplayEffect
{
	GENERATED_BODY()
	
public:
	
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="AbilityAsset",meta=(RowType="/Script/ElGaTo.GaToEffectData"))
	TObjectPtr<UDataTable> EffectTable;
	
	UFUNCTION(BlueprintCallable)
	FName GetEffectName() const;
#if WITH_EDITOR
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	
private:
	UFUNCTION(BlueprintCallable,CallInEditor)
	void AddToTable();
		
	
	
#endif
};
