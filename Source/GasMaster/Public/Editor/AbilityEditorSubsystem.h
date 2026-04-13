// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "AbilityEditorSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ELGATO_API UAbilityEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	TObjectPtr<UDataTable> GetAbilityTable();
	TObjectPtr<UDataTable> GetEffectTable();
	TObjectPtr<UStringTable> GetAbilityStringTable();
	TObjectPtr<UStringTable> GetEffectStringTable();
	
};
