// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GaMaAbilitySystemComponent.h"


// Sets default values for this component's properties
UGaMaAbilitySystemComponent::UGaMaAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGaMaAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGaMaAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGaMaAbilitySystemComponent::NotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability,
	bool bWasCancelled)
{
	Super::NotifyAbilityEnded(Handle, Ability, bWasCancelled);
	OnAbilityEnded.Broadcast(Ability,Ability->GetAssetTags(),bWasCancelled);
}

FGameplayTagContainer UGaMaAbilitySystemComponent::GetAssetTags(UGameplayAbility* ability)
{
	return ability->GetAssetTags();
}

