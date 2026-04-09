// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GaToAtributeSetInitter.h"


FGaToAtributeSetInitter::FGaToAtributeSetInitter()
{
}

FGaToAtributeSetInitter::~FGaToAtributeSetInitter()
{
}

void FGaToAtributeSetInitter::PreloadAttributeSetData(const TArray<UCurveTable*>& CurveData)
{
}

void FGaToAtributeSetInitter::InitAttributeSetDefaults(UAbilitySystemComponent* AbilitySystemComponent, FName GroupName,
	int32 Level, bool bInitialInit) const
{
}

void FGaToAtributeSetInitter::ApplyAttributeDefault(UAbilitySystemComponent* AbilitySystemComponent,
	FGameplayAttribute& InAttribute, FName GroupName, int32 Level) const
{
}

TArray<float> FGaToAtributeSetInitter::GetAttributeSetValues(UClass* AttributeSetClass, FProperty* AttributeProperty,
	FName GroupName) const
{
	return FAttributeSetInitter::GetAttributeSetValues(AttributeSetClass, AttributeProperty, GroupName);
}
