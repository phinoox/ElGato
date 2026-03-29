// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UObject/Object.h"
#include "FAttributeData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAttributeData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttribute Attribute;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttributeData MaxAttribute;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
};