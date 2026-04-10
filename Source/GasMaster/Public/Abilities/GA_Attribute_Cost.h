// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Abilities/GameplayAbility.h"
#include "Base/GaToGameplayAbilityBase.h"
#include "GA_Attribute_Cost.generated.h"

UENUM(BlueprintType)
enum class EABilityInputId : uint8
{
	None UMETA(DisplayName = "none"),
	Primary,
	Secondary,
	Defensive,
	Movement
};
/**
 * 
 */
UCLASS()
class ELGATO_API UGA_Attribute_Cost : public UGaToGameplayAbilityBase
{
	GENERATED_BODY()
public:
	UGA_Attribute_Cost();
	public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="General")
	bool ActivateWhenGranted=false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Costs")
	FGameplayAttribute CostAttribute;
		
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Costs")
	float AbilityCosts;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Costs")
	bool CanExceedZero;;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Costs")
	FGameplayTag CostTag;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Cooldowns")
	float CooldownDuration;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Cooldowns")
	int CooldownTriggerUses = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Cooldowns")
	float CooldownTriggerTimeOut = .25f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Cooldowns")
	FGameplayTag CooldownTag;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Cooldowns")
	int ActivationCount = 0;
	
public:
	EABilityInputId InputId = EABilityInputId::None;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	virtual  bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	
	virtual bool CommitAbilityCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FGameplayTagContainer* OptionalRelevantTags = nullptr) override;
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	
	virtual bool CommitAbilityCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const bool ForceCooldown, FGameplayTagContainer* OptionalRelevantTags = nullptr) override;
	
	virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FGameplayTagContainer* OptionalRelevantTags = nullptr) override;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
protected:
	FDateTime LastActivationTime;
};
