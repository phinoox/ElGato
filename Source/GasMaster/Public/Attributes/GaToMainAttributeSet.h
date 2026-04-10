// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GaToBaseAttributeSet.h"

#include "GaToMainAttributeSet.generated.h"


/**
 * Attributeset for basic Attributes common in most Games
 */
UCLASS()
class ELGATO_API UGaToMainAttributeSet : public UGaToBaseAttributeSet
{
	GENERATED_BODY()
	
	
public:
	bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
public:
	
	UPROPERTY()
	FPGaToAttributeEvent OnLevelChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData Level = 1;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, Level);
	
	UPROPERTY()
	FPGaToAttributeEvent OnHealthChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData Health;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, Health);
	
	UPROPERTY()
	FPGaToAttributeEvent OnMaxHealthChanged;
	
	UPROPERTY(BlueprintReadOnly,meta = (InitialValue = "Levelbased"), Category="MainAttributes")
	FGameplayAttributeData MaxHealth;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, MaxHealth);
	
	
	UPROPERTY()
	FPGaToAttributeEvent OnManaChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData Mana;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, Mana);
	
	UPROPERTY()
	FPGaToAttributeEvent OnMaxManaChanged;
	
	UPROPERTY(BlueprintReadOnly,meta = (InitialValue = "Levelbased"), Category="MainAttributes")
	FGameplayAttributeData MaxMana;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, MaxMana);
	
	UPROPERTY()
	FPGaToAttributeEvent OnShieldChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData Shield;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, Shield);
	
	UPROPERTY()
	FPGaToAttributeEvent OnMaxShieldChanged;
	
	UPROPERTY(BlueprintReadOnly,meta = (InitialValue = "Levelbased"), Category="MainAttributes")
	FGameplayAttributeData MaxShield;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, MaxShield);
	
	UPROPERTY()
	FPGaToAttributeEvent OnStaminaChanged;
 
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData Stamina;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, Stamina);
	
	UPROPERTY()
	FPGaToAttributeEvent OnMaxStaminaChanged;
 
	UPROPERTY(BlueprintReadOnly,meta = (InitialValue = "Levelbased"), Category="MainAttributes")
	FGameplayAttributeData MaxStamina;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, MaxStamina);
	
	UPROPERTY()
	FPGaToAttributeEvent OnStaminaRegenChanged;
 
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData StaminaRegen;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, StaminaRegen);
	
	UPROPERTY()
	FPGaToAttributeEvent OnManaRegenChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData ManaRegen;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, ManaRegen);
	
	UPROPERTY()
	FPGaToAttributeEvent OnHealthRegenChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData HealthRegen;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, HealthRegen);
	
	UPROPERTY()
	FPGaToAttributeEvent OnShieldRegenChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData ShieldRegen;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, ShieldRegen);
	
	UPROPERTY(BlueprintReadOnly, Category="MainAttributes")
	FGameplayAttributeData MetaDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, MetaDamage);
	
	UPROPERTY()
	FPGaToAttributeEvent OnWalkSpeedFactorChanged;
	
	UPROPERTY(BlueprintReadOnly,meta = (InitialValue = "Levelbased"), Category="MainAttributes")
	FGameplayAttributeData WalkSpeedFactor;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, WalkSpeedFactor);
	
	UPROPERTY()
	FPGaToAttributeEvent OnMaxWalkSpeedChanged;
	
	UPROPERTY(BlueprintReadOnly,meta = (InitialValue = "Levelbased"), Category="MainAttributes")
	FGameplayAttributeData MaxWalkSpeed;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToMainAttributeSet, MaxWalkSpeed);
};
