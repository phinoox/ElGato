// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/GaToMainAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Attributes/GaToTags.h"


bool UGaToMainAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UGaToMainAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetMetaDamageAttribute())
	{
		float TotalDamage = GetMetaDamage();
		
		SetMetaDamage(0.0f);
		
		float CurrentShield = GetShield();
		if (CurrentShield>0)
		{
			SetShield(CurrentShield-TotalDamage);
			float RemainingDamage = TotalDamage - CurrentShield;
			if (RemainingDamage > 0){
				SetHealth(GetHealth() - RemainingDamage);
			}
		}
		
		SetHealth(GetHealth()-TotalDamage);
		
		if (Data.EffectSpec.Def->GetAssetTags().HasTag(GaToTags::TAG_Character_Status_Hit) && Data.EvaluatedData.Magnitude != 0.0f)
		{
			FGameplayTagContainer TagContainer;
			TagContainer.AddTag(GaToTags::TAG_Character_Status_Hit);
			GetOwningAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(GetHealth());
		OnHealthChanged.Broadcast(Data.EvaluatedData.Magnitude, GetHealth());
		
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(GetMana());
		OnManaChanged.Broadcast(Data.EvaluatedData.Magnitude, GetMana());
	}
	else if (Data.EvaluatedData.Attribute == GetShieldAttribute())
	{
		SetShield(GetShield());
		OnShieldChanged.Broadcast(Data.EvaluatedData.Magnitude, GetShield());
	}
	else if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(GetStamina());
		OnStaminaChanged.Broadcast(Data.EvaluatedData.Magnitude, GetStamina());
	}
	else if (Data.EvaluatedData.Attribute == GetWalkSpeedFactorAttribute())
	{
		SetWalkSpeedFactor(GetWalkSpeedFactor());
		OnWalkSpeedFactorChanged.Broadcast(Data.EvaluatedData.Magnitude, GetWalkSpeedFactor());
	}
	else if (Data.EvaluatedData.Attribute == GetMaxWalkSpeedAttribute())
	{
		SetMaxWalkSpeed(GetMaxWalkSpeed());
		OnMaxWalkSpeedChanged.Broadcast(Data.EvaluatedData.Magnitude, GetMaxWalkSpeed());
	}
}

void UGaToMainAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	OnPostAttributeChanged.Broadcast(Attribute,OldValue,NewValue);
	if (Attribute== GetHealthAttribute() && NewValue == 0)
	{
		FGameplayTagContainer TagContainer;
		TagContainer.AddTag(GaToTags::TAG_Character_Status_Dead);
		if (!GetOwningAbilitySystemComponent()->TryActivateAbilitiesByTag(TagContainer))
		{
			GetOwningAbilitySystemComponent()->AddLooseGameplayTags(TagContainer);
		}
	}
	
	if (Attribute == GetMaxHealthAttribute() && GetHealth() == OldValue)
	{
		SetHealth(NewValue);
	}
	else if (Attribute == GetMaxStaminaAttribute() && GetStamina() == OldValue)
	{
		SetStamina(NewValue);
	}
	else if (Attribute == GetMaxManaAttribute() && GetMana() == OldValue)
	{
		SetMana(NewValue);
	}
	else if (Attribute == GetMaxShieldAttribute() && GetShield() == OldValue)
	{
		SetShield(NewValue);
	}
}

void UGaToMainAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue= FMath::Clamp(NewValue,0.0f,GetMaxHealth());
	}
	else if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue,0.0f,GetMaxStamina());
	}
	else if (Attribute == GetManaAttribute())
	{
		NewValue=FMath::Clamp(NewValue,0.0f,GetMaxMana());
	}
	else if (Attribute == GetShieldAttribute())
	{
		NewValue=FMath::Clamp(NewValue,0.0f,GetMaxShield());
	}
}
