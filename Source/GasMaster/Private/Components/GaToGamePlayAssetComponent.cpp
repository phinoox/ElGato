// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GaToGamePlayAssetComponent.h"
#include "AbilitySystemGlobals.h"
#include "GaToLog.h"
#include "Attributes/GaToBaseAttributeSet.h"
#include "Base/GaToGameplayEffectBase.h"
#include "Data/GaToEffectSetAsset.h"
#include "Attributes/GaToMainAttributeSet.h"
#include "Base/GaToGameplayAbilityBase.h"


// Sets default values for this component's properties
UGaToGamePlayAssetComponent::UGaToGamePlayAssetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGaToGamePlayAssetComponent::OnAttributeChanged(FGameplayAttribute Attribute, float OldValue, float NewValue)
{
	if (Attribute == UGaToMainAttributeSet::GetLevelAttribute())
	{
		InitializeAttributes();
	}
}


// Called when the game starts
void UGaToGamePlayAssetComponent::BeginPlay()
{
	Super::BeginPlay();
	// construct dummy asset if none was set
	
	AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetOwner());
	UAbilitySystemGlobals::Get().InitGlobalData();
	if (AbilitySystemComponent)
	{
		
		AbilitySystemComponent->OnGameplayEffectAppliedDelegateToSelf.AddLambda(
			[]( UAbilitySystemComponent* ASC, const FGameplayEffectSpec& spec, FActiveGameplayEffectHandle handle)
		{
			auto owner = ASC->GetAvatarActor()->GetName();
			auto effectinfo = spec.ToSimpleString();
			UE_LOG(LogGaTo,Verbose, TEXT("Effect applied to %s : %s"),*owner,*effectinfo);
		});
		AbilitySystemComponent->AbilityFailedCallbacks.AddLambda(
			[](const UGameplayAbility* ability,const FGameplayTagContainer container )
		{
			auto name = ability->GetName();
			auto containerinfo = container.ToString();
			UE_LOG(LogGaTo,Verbose, TEXT("Ability %s failed due to %s"),*name,*containerinfo);
		});
		EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(GetOwner());
		
		InitializeAttributes();
		
		if (!GameplayAssetRef.IsNull())
		{
			GameplayAsset = GameplayAssetRef.LoadSynchronous();
			Initialize();
			 UGaToMainAttributeSet* AttributeSet = const_cast<UGaToMainAttributeSet*>(Cast<UGaToMainAttributeSet>(
				AbilitySystemComponent->GetAttributeSet(UGaToMainAttributeSet::StaticClass())));
			AttributeSet->OnPostAttributeChanged.AddUniqueDynamic(this,&UGaToGamePlayAssetComponent::OnAttributeChanged);
		}
		
	}
	
}


// Called every frame
void UGaToGamePlayAssetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGaToGamePlayAssetComponent::SwitchAbilitySet(int index)
{
	
	if (AbilitySystemComponent && GameplayAsset->AbilitySets.Num() >= index)
	{
		for (FGameplayAbilitySpecHandle Ability : CurrentHandles)
		{
			AbilitySystemComponent->ClearAbility(Ability);
		}
		
		GiveAbilitySet(GameplayAsset->AbilitySets[0]);
	}   
}

void UGaToGamePlayAssetComponent::GiveAbilitySet(TSoftObjectPtr<UGaToAbilitySetAsset> AbilitySet)
{
	
	for (FDataTableRowHandle Ability : AbilitySet->Abilities)
	{
		TSubclassOf<UGaToGameplayAbilityBase> abilityclass = Ability.GetRow<FGaToAbilityData>(TEXT("AbilityData"))->
		                                                             AbilityClass;
		FGameplayAbilitySpec AbilitySpec(*abilityclass);
		FGameplayAbilitySpecHandle SpecHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
		CurrentHandles.Add(SpecHandle);
	}
}

TSubclassOf<UGaToGameplayEffectBase> UGaToGamePlayAssetComponent::GetEffect(int index)
{
	auto EffectHandle = GameplayAsset->InitialEffects->Effects[index];
	TSubclassOf<UGaToGameplayEffectBase> effectclass = EffectHandle.GetRow<FGaToEffectData>(TEXT("EffectData"))->EffectClass;
	return effectclass;
}

void UGaToGamePlayAssetComponent::Initialize()
{
	InitializeEffects();
	InitializeAbilities();
}

void UGaToGamePlayAssetComponent::InitializeAttributes()
{
	if (!IsValid(AttributeInitEffect))
		return;
	FGameplayEffectSpecHandle Spec = AbilitySystemComponent->MakeOutgoingSpec(AttributeInitEffect,1,EffectContext);
	if (Spec.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
	}
}

void UGaToGamePlayAssetComponent::InitializeAbilities()
{
	AbilitySystemComponent->SetNumericAttributeBase(UGaToMainAttributeSet::GetLevelAttribute(),CharacterLevel);
	
	if (GameplayAsset->AbilitySets.Num() > 0)
	{
		for (FDataTableRowHandle Ability : GameplayAsset->AbilitySets[0]->Abilities)
		{
			auto AbilityEntry = Ability.GetRow<FGaToAbilityData>(TEXT("AbilityData"));
			if (!AbilityEntry)
				continue;
			UE_LOG(LogGaTo,Display, TEXT("Trying to add ability %s character"),*AbilityEntry->DisplayName.ToString());
			TSubclassOf<UGaToGameplayAbilityBase> abilityclass = AbilityEntry->AbilityClass;
			FGameplayAbilitySpec AbilitySpec(*abilityclass);
			AbilitySystemComponent->GiveAbility(AbilitySpec);
		}
	}
	
	if (GameplayAsset->ReactiveAbilities != nullptr)
	{
		for (FDataTableRowHandle Ability : GameplayAsset->ReactiveAbilities->Abilities)
		{
			if (Ability.IsNull() || Ability.RowName.IsNone())
				continue;;
			TSubclassOf<UGaToGameplayAbilityBase> abilityclass = Ability.GetRow<FGaToAbilityData>(TEXT("AbilityData"))->
																		 AbilityClass;
			FGameplayAbilitySpec AbilitySpec(*abilityclass);
			AbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);
		}
	}
}

void UGaToGamePlayAssetComponent::InitializeEffects()
{
	if (GameplayAsset->InitialEffects == nullptr )
		return;
	for (auto& Effect : GameplayAsset->InitialEffects->Effects)
	{
		if (Effect.IsNull() || Effect.RowName.IsNone())
			continue;
		TSubclassOf<UGaToGameplayEffectBase> effectclass = Effect.GetRow<FGaToEffectData>(TEXT("EffectData"))->
																	 EffectClass;
		FGameplayEffectSpecHandle Spec = AbilitySystemComponent->MakeOutgoingSpec(effectclass,1,EffectContext);
		if (Spec.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
		}
	}
}





