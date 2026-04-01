// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GaMaBaseAttributeSet.h"
#include "GaMaElementalAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class GASMASTER_API UGaMaElementalAttributeSet : public UGaMaBaseAttributeSet
{
	GENERATED_BODY()
	
public:
	bool PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data) override;
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	
	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
public:
	
	UPROPERTY()
	FPGaMaAttributeEvent OnWindDamageChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData WindDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, WindDamage);

	UPROPERTY()
	FPGaMaAttributeEvent OnFireDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData FireDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, FireDamage);

	UPROPERTY()
	FPGaMaAttributeEvent OnIceDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData IceDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, IceDamage);

	

	UPROPERTY()
	FPGaMaAttributeEvent OnEarthDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData EarthDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, EarthDamage);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnWindResistanceChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData WindResistance;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, WindResistance);

	UPROPERTY()
	FPGaMaAttributeEvent OnFireResistanceChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData FireResistance;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, FireResistance);

	UPROPERTY()
	FPGaMaAttributeEvent OnIceResistanceChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData IceResistance;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, IceResistance);

	UPROPERTY()
	FPGaMaAttributeEvent OnEarthResistanceChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData EarthResistance;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, EarthResistance);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnWaterDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData WaterDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, WaterDamage);
	

	UPROPERTY()
	FPGaMaAttributeEvent OnWaterResistanceChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData WaterResistance;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, WaterResistance);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnLightningDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData LightningDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, LightningDamage);
	
	UPROPERTY()
	FPGaMaAttributeEvent OnHolyDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData HolyDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, HolyDamage);

	UPROPERTY()
	FPGaMaAttributeEvent OnDarkDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData DarkDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, DarkDamage);

	UPROPERTY()
	FPGaMaAttributeEvent OnPoisonDamageChanged;

	UPROPERTY(BlueprintReadOnly, Category="ElementAttributes")
	FGameplayAttributeData PoisonDamage;
	PLAY_ATTRIBUTE_ACCESSORS(UGaMaElementalAttributeSet, PoisonDamage);
	
};
