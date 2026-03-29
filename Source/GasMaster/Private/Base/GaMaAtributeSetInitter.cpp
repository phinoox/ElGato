// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GaMaAtributeSetInitter.h"


FGaMaAtributeSetInitter::FGaMaAtributeSetInitter()
{
}

FGaMaAtributeSetInitter::~FGaMaAtributeSetInitter()
{
}

void FGaMaAtributeSetInitter::PreloadAttributeSetData(const TArray<UCurveTable*>& CurveData)
{
}

void FGaMaAtributeSetInitter::InitAttributeSetDefaults(UAbilitySystemComponent* AbilitySystemComponent, FName GroupName,
	int32 Level, bool bInitialInit) const
{
}

void FGaMaAtributeSetInitter::ApplyAttributeDefault(UAbilitySystemComponent* AbilitySystemComponent,
	FGameplayAttribute& InAttribute, FName GroupName, int32 Level) const
{
}

TArray<float> FGaMaAtributeSetInitter::GetAttributeSetValues(UClass* AttributeSetClass, FProperty* AttributeProperty,
	FName GroupName) const
{
	return FAttributeSetInitter::GetAttributeSetValues(AttributeSetClass, AttributeProperty, GroupName);
}
