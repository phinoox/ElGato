// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GaMaBaseAttributeSet.h"

#include "GaMaMainAttributeSet.generated.h"


/**
 * Attributeset for basic Attributes common in most Games
 */
UCLASS()
class GASMASTER_API UGaMaMainAttributeSet : public UGaMaBaseAttributeSet
{
	GENERATED_BODY()
	
	
public:
	bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
public:
	
	UPROPERTY()
	FPGaMaAttributeEvent OnLevelChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData Level = 1;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, Level);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnHealthChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData Health;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, Health);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnMaxHealthChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData MaxHealth;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, MaxHealth);
	
	
	UPROPERTY()
	FPGaMaAttributeEvent OnManaChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData Mana;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, Mana);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnMaxManaChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData MaxMana;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, MaxMana);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnShieldChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData Shield;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, Shield);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnMaxShieldChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData MaxShield;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, MaxShield);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnStaminaChanged;
 
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData Stamina;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, Stamina);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnMaxStaminaChanged;
 
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData MaxStamina;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, MaxStamina);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnStaminaRegenChanged;
 
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData StaminaRegen;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, StaminaRegen);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnManaRegenChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData ManaRegen;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, ManaRegen);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnHealthRegenChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData HealthRegen;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, HealthRegen);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnShieldRegenChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData ShieldRegen;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, ShieldRegen);
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData MetaDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaMainAttributeSet, MetaDamage);
};
