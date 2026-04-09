// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GaToBaseAttributeSet.h"
#include "GaToElementalAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class GASMASTER_API UGaToElementalAttributeSet : public UGaToBaseAttributeSet
{
	GENERATED_BODY()
	
public:
	bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
public:
	
	UPROPERTY()
	FPGaToAttributeEvent OnWindDamageChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData WindDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, WindDamage);

	UPROPERTY()
	FPGaToAttributeEvent OnFireDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData FireDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, FireDamage);

	UPROPERTY()
	FPGaToAttributeEvent OnIceDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData IceDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, IceDamage);

	

	UPROPERTY()
	FPGaToAttributeEvent OnEarthDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData EarthDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, EarthDamage);
	
	UPROPERTY()
	FPGaToAttributeEvent OnWindResistanceChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData WindResistance;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, WindResistance);

	UPROPERTY()
	FPGaToAttributeEvent OnFireResistanceChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData FireResistance;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, FireResistance);

	UPROPERTY()
	FPGaToAttributeEvent OnIceResistanceChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData IceResistance;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, IceResistance);

	UPROPERTY()
	FPGaToAttributeEvent OnEarthResistanceChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData EarthResistance;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, EarthResistance);
	
	UPROPERTY()
	FPGaToAttributeEvent OnWaterDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData WaterDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, WaterDamage);
	

	UPROPERTY()
	FPGaToAttributeEvent OnWaterResistanceChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData WaterResistance;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, WaterResistance);
	
	UPROPERTY()
	FPGaToAttributeEvent OnLightningDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData LightningDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, LightningDamage);
	
	UPROPERTY()
	FPGaToAttributeEvent OnHolyDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData HolyDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, HolyDamage);

	UPROPERTY()
	FPGaToAttributeEvent OnDarkDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData DarkDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, DarkDamage);

	UPROPERTY()
	FPGaToAttributeEvent OnPoisonDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData PoisonDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaToElementalAttributeSet, PoisonDamage);
	
};
