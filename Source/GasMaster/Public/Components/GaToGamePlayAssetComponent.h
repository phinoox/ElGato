// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/GaToGameplayAsset.h"
#include "AbilitySystemComponent.h"
#include "GaToGamePlayAssetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ELGATO_API UGaToGamePlayAssetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGaToGamePlayAssetComponent();

protected:
	UFUNCTION()
	void OnAttributeChanged(FGameplayAttribute Attribute, float OldValue, float NewValue);
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	FGameplayEffectContextHandle EffectContext;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	int CharacterLevel=1;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	TSoftObjectPtr<UGaToGameplayAsset> GameplayAssetRef;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	TObjectPtr<UGaToGameplayAsset> GameplayAsset;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	FGameplayTagContainer InitialTags;
		
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category="Ability Set")
	TObjectPtr<UDataTable> AttributeTable;
	
	UFUNCTION(BlueprintCallable)
	void SwitchAbilitySet(int index);
	
	UFUNCTION(BlueprintCallable)
	void GiveAbilitySet(TSoftObjectPtr<UGaToAbilitySetAsset> AbilitySet);
	
	UFUNCTION()
	TSubclassOf<UGaToGameplayEffectBase> GetEffect(int index);

	
private:
	void Initialize();
	void InitializeAttributes();
	void InitializeAbilities();
	void InitializeTags();
	void InitializeEffects();
	int CurrentAbilitySet = 0;
	TArray<FGameplayAbilitySpecHandle> CurrentHandles;
};


