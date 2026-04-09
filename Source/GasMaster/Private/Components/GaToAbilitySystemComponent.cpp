// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GaToAbilitySystemComponent.h"


// Sets default values for this component's properties
UGaToAbilitySystemComponent::UGaToAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGaToAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGaToAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGaToAbilitySystemComponent::NotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability,
	bool bWasCancelled)
{
	Super::NotifyAbilityEnded(Handle, Ability, bWasCancelled);
	OnAbilityEnded.Broadcast(Ability,Ability->GetAssetTags(),bWasCancelled);
}

FGameplayTagContainer UGaToAbilitySystemComponent::GetAssetTags(UGameplayAbility* ability)
{
	return ability->GetAssetTags();
}

