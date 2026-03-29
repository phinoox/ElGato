// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/GaMaBaseAttributeSet.h"

#include "GameplayEffectExtension.h"



void UGaMaBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	OnPreAttributeChanged.Broadcast(Attribute, NewValue);
}

void UGaMaBaseAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	OnPostAttributeChanged.Broadcast(Attribute,OldValue,NewValue);
}

bool UGaMaBaseAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	OnPreGameplayEffectExecute.Broadcast(Data.EvaluatedData,Data.EffectSpec,&Data.Target);
	//OnPreGameplayEffectExecute.Broadcast(Data);
	return Super::PreGameplayEffectExecute(Data);
}

void UGaMaBaseAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	OnPostGameplayEffectExecute.Broadcast(Data.EvaluatedData,Data.EffectSpec,&Data.Target);
}

