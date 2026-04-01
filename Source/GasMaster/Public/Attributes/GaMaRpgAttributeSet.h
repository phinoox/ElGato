// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GaMaBaseAttributeSet.h"
#include "GaMaRpgAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class GASMASTER_API UGaMaRpgAttributeSet : public UGaMaBaseAttributeSet
{
	GENERATED_BODY()
	
public:
	bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
public:
	UPROPERTY()
	FPGaMaAttributeEvent OnHealthChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Health;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaRpgAttributeSet, Health);

	UPROPERTY()
	FPGaMaAttributeEvent OnStrengthChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Strength;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaRpgAttributeSet, Strength);

	UPROPERTY()
	FPGaMaAttributeEvent OnDexterityChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Dexterity;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaRpgAttributeSet, Dexterity);

	UPROPERTY()
	FPGaMaAttributeEvent OnConstitutionChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Constitution;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaRpgAttributeSet, Constitution);

	UPROPERTY()
	FPGaMaAttributeEvent OnIntelligenceChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Intelligence;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaRpgAttributeSet, Intelligence);

	UPROPERTY()
	FPGaMaAttributeEvent OnWisdomChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Wisdom;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaRpgAttributeSet, Wisdom);

	UPROPERTY()
	FPGaMaAttributeEvent OnCharismaChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Charisma;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaRpgAttributeSet, Charisma);

	UPROPERTY()
	FPGaMaAttributeEvent OnLuckChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Luck;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaRpgAttributeSet, Luck);

	UPROPERTY()
	FPGaMaAttributeEvent OnSpeedChanged;

	UPROPERTY(BlueprintReadOnly, Category="RpgAttributes")
	FGameplayAttributeData Speed;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaRpgAttributeSet, Speed);
};
