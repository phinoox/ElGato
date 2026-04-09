// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GaToAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ElGaTo_API UGaToAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGaToAbilitySystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAbilityEnded, UGameplayAbility*, Ability,FGameplayTagContainer,AssetTags,bool, bWasCanceled);
	UPROPERTY(BlueprintAssignable)
	FOnAbilityEnded OnAbilityEnded;
	
	virtual void NotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, bool bWasCancelled) override;
	
	UFUNCTION(BlueprintCallable)
	FGameplayTagContainer GetAssetTags(UGameplayAbility* ability);
};
