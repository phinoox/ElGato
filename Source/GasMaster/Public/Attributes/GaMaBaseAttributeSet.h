// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffect.h"
#include "GaMaBaseAttributeSet.generated.h"

#define PLAY_ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \

class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPGaMaAttributeEvent, float, EffectMagnitude, float, NewValue);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPreAttributeChanged, FGameplayAttribute, Attribute,float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPostAttributeChanged, FGameplayAttribute, Attribute,float,OldValue, float,NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPreGameplayEffectExecute, const FGameplayModifierEvaluatedData& , Data,const FGameplayEffectSpec&, Spec, UAbilitySystemComponent*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnPostGameplayEffectExecute, const FGameplayModifierEvaluatedData& , Data,const FGameplayEffectSpec&, Spec, UAbilitySystemComponent*, Target);

/**
 * Basic AttributeSet with general events for changes
 */
UCLASS()
class GASMASTER_API UGaMaBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintAssignable)
	FOnPreAttributeChanged OnPreAttributeChanged;
	
	
	UPROPERTY(BlueprintAssignable)
	FOnPostAttributeChanged OnPostAttributeChanged;
	
	
	UPROPERTY(BlueprintAssignable)
	FOnPreGameplayEffectExecute OnPreGameplayEffectExecute;
	
	
	UPROPERTY(BlueprintAssignable)
	FOnPostGameplayEffectExecute OnPostGameplayEffectExecute;
	
	
	
public:
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual bool PreGameplayEffectExecute( FGameplayEffectModCallbackData &Data) override;
	virtual void PostGameplayEffectExecute(const  FGameplayEffectModCallbackData& Data) override;
	
	
};
