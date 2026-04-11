// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ElGaToSettings.generated.h"

/**
 * 
 */
UCLASS(config = ElGaTo,DefaultConfig)
class ELGATO_API UElGaToSettings : public UObject
{
	GENERATED_BODY()
public:
	UElGaToSettings(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(Config,EditAnywhere,meta = (LongPackageName),Category="ElGaTo Settings")
	FDirectoryPath AssetBasePath = FDirectoryPath("/Game/Data");
};
