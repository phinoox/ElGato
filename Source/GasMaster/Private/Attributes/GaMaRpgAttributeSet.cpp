// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/GaMaRpgAttributeSet.h"

#include "GameplayEffectExtension.h"

bool UGaMaRpgAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UGaMaRpgAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetStrengthAttribute())
	{
		SetStrength(GetStrength());
		OnStrengthChanged.Broadcast(Data.EvaluatedData.Magnitude, GetStrength());
	}
	else if (Data.EvaluatedData.Attribute == GetDexterityAttribute())
	{
		SetDexterity(GetDexterity());
		OnDexterityChanged.Broadcast(Data.EvaluatedData.Magnitude, GetDexterity());
	}
	else if (Data.EvaluatedData.Attribute == GetConstitutionAttribute())
	{
		SetConstitution(GetConstitution());
		OnConstitutionChanged.Broadcast(Data.EvaluatedData.Magnitude, GetConstitution());
	}
	else if (Data.EvaluatedData.Attribute == GetIntelligenceAttribute())
	{
		SetIntelligence(GetIntelligence());
		OnIntelligenceChanged.Broadcast(Data.EvaluatedData.Magnitude, GetIntelligence());
	}
	else if (Data.EvaluatedData.Attribute == GetWisdomAttribute())
	{
		SetWisdom(GetWisdom());
		OnWisdomChanged.Broadcast(Data.EvaluatedData.Magnitude, GetWisdom());
	}
	else if (Data.EvaluatedData.Attribute == GetCharismaAttribute())
	{
		SetCharisma(GetCharisma());
		OnCharismaChanged.Broadcast(Data.EvaluatedData.Magnitude, GetCharisma());
	}
	else if (Data.EvaluatedData.Attribute == GetLuckAttribute())
	{
		SetLuck(GetLuck());
		OnLuckChanged.Broadcast(Data.EvaluatedData.Magnitude, GetLuck());
	}
	else if (Data.EvaluatedData.Attribute == GetSpeedAttribute())
	{
		SetSpeed(GetSpeed());
		OnSpeedChanged.Broadcast(Data.EvaluatedData.Magnitude, GetSpeed());
	}
}

void UGaMaRpgAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UGaMaRpgAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}
