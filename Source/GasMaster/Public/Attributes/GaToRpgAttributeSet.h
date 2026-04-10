// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GaToBaseAttributeSet.h"
#include "GaToRpgAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ELGATO_API UGaToRpgAttributeSet : public UGaToBaseAttributeSet
{
	GENERATED_BODY()
	
public:
	bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
public:
	UPROPERTY()
	FPGaToAttributeEvent OnHealthChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Health;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToRpgAttributeSet, Health);

	UPROPERTY()
	FPGaToAttributeEvent OnStrengthChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Strength;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToRpgAttributeSet, Strength);

	UPROPERTY()
	FPGaToAttributeEvent OnDexterityChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Dexterity;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToRpgAttributeSet, Dexterity);

	UPROPERTY()
	FPGaToAttributeEvent OnConstitutionChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Constitution;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToRpgAttributeSet, Constitution);

	UPROPERTY()
	FPGaToAttributeEvent OnIntelligenceChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Intelligence;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToRpgAttributeSet, Intelligence);

	UPROPERTY()
	FPGaToAttributeEvent OnWisdomChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Wisdom;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToRpgAttributeSet, Wisdom);

	UPROPERTY()
	FPGaToAttributeEvent OnCharismaChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Charisma;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToRpgAttributeSet, Charisma);

	UPROPERTY()
	FPGaToAttributeEvent OnLuckChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Luck;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToRpgAttributeSet, Luck);

	UPROPERTY()
	FPGaToAttributeEvent OnSpeedChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Speed;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToRpgAttributeSet, Speed);
};
