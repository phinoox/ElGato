// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/GA_Attribute_Cost.h"

#include "AbilitySystemComponent.h"
#include "GaToLog.h"
#include "Attributes/GaToTags.h"

UGA_Attribute_Cost::UGA_Attribute_Cost()
{
	ActivationOwnedTags.AddTag(GaToTags::TAG_Abilities_General_Active);
	ActivationBlockedTags.AddTag(GaToTags::TAG_Character_Status_Dead);
	LastActivationTime = FDateTime::Now();
}

void UGA_Attribute_Cost::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	LastActivationTime = FDateTime::Now();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UGA_Attribute_Cost::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                   FGameplayTagContainer* OptionalRelevantTags) const
{
	if (CanExceedZero)
		return true;
	if (!CostAttribute.IsValid())
		return false;
	auto CostCheck = ActorInfo->AbilitySystemComponent->GetNumericAttribute(CostAttribute) >= AbilityCosts;
	if (!CostCheck)
	{
		UE_LOG(LogGaTo,Verbose, TEXT("Could ot   spend   %s   to   activate   ability   %s."),*CostAttribute.AttributeName, *GetClass()->GetName());
	}
	return CostCheck;
}

bool UGA_Attribute_Cost::CommitAbilityCost(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	FGameplayTagContainer* OptionalRelevantTags)
{
	if (!CostGameplayEffectClass)
		return true;
	if (!CheckCost(Handle, ActorInfo, OptionalRelevantTags))
		return false;
	auto asc = ActorInfo->AbilitySystemComponent;
	FGameplayEffectContextHandle EffectContext = asc->MakeEffectContext();
	FGameplayEffectSpecHandle Spec = asc->MakeOutgoingSpec(CostGameplayEffectClass, 0, EffectContext);
	Spec.Data->SetByCallerTagMagnitudes.Add(CostTag,AbilityCosts * -1.0f);
	auto EffectHandle = asc->ApplyGameplayEffectSpecToSelf(*Spec.Data);
	return EffectHandle.WasSuccessfullyApplied();
	
}

bool UGA_Attribute_Cost::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!CheckCost(Handle, ActorInfo, OptionalRelevantTags))
		return false;
	bool CanActivate = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	if (!CanActivate)
	{
		UE_LOG(LogGaTo,Verbose, TEXT("could not activate ability"));
	}
	return CanActivate;
}

bool UGA_Attribute_Cost::CommitAbilityCooldown(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const bool ForceCooldown, FGameplayTagContainer* OptionalRelevantTags)
{
	ActivationCount++;
	if (!CooldownGameplayEffectClass)
		return true;
	if (CooldownTriggerUses!=0)
	{
		if (ActivationCount%CooldownTriggerUses!=0)
		{
			return true;
		}
	}
	auto asc = ActorInfo->AbilitySystemComponent;
	FGameplayEffectContextHandle EffectContext = asc->MakeEffectContext();
	FGameplayEffectSpecHandle Spec = asc->MakeOutgoingSpec(CooldownGameplayEffectClass, 0, EffectContext);
	Spec.Data->SetByCallerTagMagnitudes.Add(CooldownTag,CooldownDuration);
	auto EffectHandle = asc->ApplyGameplayEffectSpecToSelf(*Spec.Data);
	ActivationCount=0;
	return EffectHandle.WasSuccessfullyApplied();
	
	return Super::CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, ForceCooldown, OptionalRelevantTags);
}

bool UGA_Attribute_Cost::CommitAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	FGameplayTagContainer* OptionalRelevantTags)
{
	
	if (!CommitAbilityCost(Handle,ActorInfo,ActivationInfo,OptionalRelevantTags))
		return false;
	if (CommitAbilityCooldown(Handle,ActorInfo,ActivationInfo,OptionalRelevantTags))
		return false;
	return true;
	return Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags);
}

void UGA_Attribute_Cost::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (FDateTime::Now() - LastActivationTime > CooldownTriggerTimeOut)
	{
		ActivationCount = 0;
	}
}
