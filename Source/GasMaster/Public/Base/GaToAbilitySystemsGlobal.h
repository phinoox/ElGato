// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "GaToAbilitySystemsGlobal.generated.h"

/**
 * 
 */
UCLASS()
class GASMASTER_API UGaToAbilitySystemsGlobal : public UAbilitySystemGlobals
{
	GENERATED_BODY()
public:
	virtual void AllocAttributeSetInitter() override;
};
