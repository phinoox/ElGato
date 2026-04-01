// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/GaMaElementalAttributeSet.h"

#include "GameplayEffectExtension.h"

bool UGaMaElementalAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UGaMaElementalAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetWindDamageAttribute())
	{
		SetWindDamage(GetWindDamage());
		OnWindDamageChanged.Broadcast(Data.EvaluatedData.Magnitude, GetWindDamage());
	}
	else if (Data.EvaluatedData.Attribute == GetFireDamageAttribute())
	{
		SetFireDamage(GetFireDamage());
		OnFireDamageChanged.Broadcast(Data.EvaluatedData.Magnitude, GetFireDamage());
	}
	else if (Data.EvaluatedData.Attribute == GetEarthDamageAttribute())
	{
		SetEarthDamage(GetEarthDamage());
		OnEarthDamageChanged.Broadcast(Data.EvaluatedData.Magnitude, GetEarthDamage());
	}
	else if (Data.EvaluatedData.Attribute == GetWaterDamageAttribute())
	{
		SetWaterDamage(GetWaterDamage());
		OnWaterDamageChanged.Broadcast(Data.EvaluatedData.Magnitude, GetWaterDamage());
	}

	if (Data.EvaluatedData.Attribute == GetEarthResistanceAttribute())
	{
		SetEarthResistance(GetEarthResistance());
		OnEarthResistanceChanged.Broadcast(Data.EvaluatedData.Magnitude, GetEarthResistance());
	}
	else if (Data.EvaluatedData.Attribute == GetWaterResistanceAttribute())
	{
		SetWaterResistance(GetWaterResistance());
		OnWaterResistanceChanged.Broadcast(Data.EvaluatedData.Magnitude, GetWaterResistance());
	}
	else if (Data.EvaluatedData.Attribute == GetFireResistanceAttribute())
	{
		SetFireResistance(GetFireResistance());
		OnFireResistanceChanged.Broadcast(Data.EvaluatedData.Magnitude, GetFireResistance());
	}
	else if (Data.EvaluatedData.Attribute == GetWindResistanceAttribute())
	{
		SetWindResistance(GetWindResistance());
		OnWindResistanceChanged.Broadcast(Data.EvaluatedData.Magnitude, GetWindResistance());
	}
	else if (Data.EvaluatedData.Attribute == GetIceDamageAttribute())
	{
		SetIceDamage(GetIceDamage());
		OnIceDamageChanged.Broadcast(Data.EvaluatedData.Magnitude, GetIceDamage());
	}
	else if (Data.EvaluatedData.Attribute == GetIceResistanceAttribute())
	{
		SetIceResistance(GetIceResistance());
		OnIceResistanceChanged.Broadcast(Data.EvaluatedData.Magnitude, GetIceResistance());
	}
	else if (Data.EvaluatedData.Attribute == GetLightningDamageAttribute())
	{
		SetLightningDamage(GetLightningDamage());
		OnLightningDamageChanged.Broadcast(Data.EvaluatedData.Magnitude, GetLightningDamage());
	}
	else if (Data.EvaluatedData.Attribute == GetHolyDamageAttribute())
	{
		SetHolyDamage(GetHolyDamage());
		OnHolyDamageChanged.Broadcast(Data.EvaluatedData.Magnitude, GetHolyDamage());
	}
	else if (Data.EvaluatedData.Attribute == GetDarkDamageAttribute())
	{
		SetDarkDamage(GetDarkDamage());
		OnDarkDamageChanged.Broadcast(Data.EvaluatedData.Magnitude, GetDarkDamage());
	}
	else if (Data.EvaluatedData.Attribute == GetPoisonDamageAttribute())
	{
		SetPoisonDamage(GetPoisonDamage());
		OnPoisonDamageChanged.Broadcast(Data.EvaluatedData.Magnitude, GetPoisonDamage());
	}
}

void UGaMaElementalAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue,
                                                     float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	OnPostAttributeChanged.Broadcast(Attribute, OldValue, NewValue);
}

void UGaMaElementalAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}
