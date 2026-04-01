// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/GaMaGamePlayAssetComponent.h"
#include "AbilitySystemGlobals.h"
//#include "Base/GaMaCharacterBase.h"
#include "GaMaLog.h"
#include "Attributes/GaMaBaseAttributeSet.h"
#include "Base/GaMaGameplayEffectBase.h"
#include "Data/GaMaEffectSetAsset.h"
#include "Attributes/GaMaMainAttributeSet.h"
#include "Base/GaMaGameplayAbilityBase.h"


// Sets default values for this component's properties
UGaMaGamePlayAssetComponent::UGaMaGamePlayAssetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGaMaGamePlayAssetComponent::OnAttributeChanged(FGameplayAttribute Attribute, float OldValue, float NewValue)
{
	if (Attribute == UGaMaMainAttributeSet::GetLevelAttribute())
	{
		InitializeAttributes();
	}
}


// Called when the game starts
void UGaMaGamePlayAssetComponent::BeginPlay()
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
			UE_LOG(LogGasMaster,Verbose, TEXT("Effect applied to %s : %s"),*owner,*effectinfo);
		});
		AbilitySystemComponent->AbilityFailedCallbacks.AddLambda(
			[](const UGameplayAbility* ability,const FGameplayTagContainer container )
		{
			auto name = ability->GetName();
			auto containerinfo = container.ToString();
				//auto info = ability->
			UE_LOG(LogGasMaster,Verbose, TEXT("Ability %s failed due to %s"),*name,*containerinfo);
		});
		EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(GetOwner());
		
		InitializeAttributes();
		
		if (!GameplayAssetRef.IsNull())
		{
			GameplayAsset = GameplayAssetRef.LoadSynchronous();
			Initialize();
			 UGaMaMainAttributeSet* AttributeSet = const_cast<UGaMaMainAttributeSet*>(Cast<UGaMaMainAttributeSet>(
				AbilitySystemComponent->GetAttributeSet(UGaMaMainAttributeSet::StaticClass())));
			AttributeSet->OnPostAttributeChanged.AddUniqueDynamic(this,&UGaMaGamePlayAssetComponent::OnAttributeChanged);
		}
		
	}
	
}


// Called every frame
void UGaMaGamePlayAssetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGaMaGamePlayAssetComponent::SwitchAbilitySet(int index)
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

void UGaMaGamePlayAssetComponent::GiveAbilitySet(TSoftObjectPtr<UGaMaAbilitySetAsset> AbilitySet)
{
	
	for (FDataTableRowHandle Ability : AbilitySet->Abilities)
	{
		TSubclassOf<UGaMaGameplayAbilityBase> abilityclass = Ability.GetRow<FGaMaAbilityData>(TEXT("AbilityData"))->
		                                                             AbilityClass;
		FGameplayAbilitySpec AbilitySpec(*abilityclass);
		FGameplayAbilitySpecHandle SpecHandle = AbilitySystemComponent->GiveAbility(AbilitySpec);
		CurrentHandles.Add(SpecHandle);
	}
}

TSubclassOf<UGaMaGameplayEffectBase> UGaMaGamePlayAssetComponent::GetEffect(int index)
{
	auto EffectHandle = GameplayAsset->InitialEffects->Effects[index];
	TSubclassOf<UGaMaGameplayEffectBase> effectclass = EffectHandle.GetRow<FGaMaEffectData>(TEXT("EffectData"))->EffectClass;
	return effectclass;
}

void UGaMaGamePlayAssetComponent::Initialize()
{
	//InitializeAttributes();
	InitializeEffects();
	InitializeAbilities();
}

void UGaMaGamePlayAssetComponent::InitializeAttributes()
{
	if (!IsValid(AttributeInitEffect))
		return;
	FGameplayEffectSpecHandle Spec = AbilitySystemComponent->MakeOutgoingSpec(AttributeInitEffect,1,EffectContext);
	if (Spec.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
	}
}

void UGaMaGamePlayAssetComponent::InitializeAbilities()
{
	AbilitySystemComponent->SetNumericAttributeBase(UGaMaMainAttributeSet::GetLevelAttribute(),CharacterLevel);
	
	if (GameplayAsset->AbilitySets.Num() > 0)
	{
		for (FDataTableRowHandle Ability : GameplayAsset->AbilitySets[0]->Abilities)
		{
			auto AbilityEntry = Ability.GetRow<FGaMaAbilityData>(TEXT("AbilityData"));
			UE_LOG(LogTemp,Display, TEXT("Trying to add ability %s character"),*AbilityEntry->DisplayName.ToString());
			TSubclassOf<UGaMaGameplayAbilityBase> abilityclass = AbilityEntry->AbilityClass;
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
			TSubclassOf<UGaMaGameplayAbilityBase> abilityclass = Ability.GetRow<FGaMaAbilityData>(TEXT("AbilityData"))->
																		 AbilityClass;
			FGameplayAbilitySpec AbilitySpec(*abilityclass);
			AbilitySystemComponent->GiveAbilityAndActivateOnce(AbilitySpec);
		}
	}
}

void UGaMaGamePlayAssetComponent::InitializeEffects()
{
	if (GameplayAsset->InitialEffects == nullptr )
		return;
	for (auto& Effect : GameplayAsset->InitialEffects->Effects)
	{
		if (Effect.IsNull() || Effect.RowName.IsNone())
			continue;
		TSubclassOf<UGaMaGameplayEffectBase> effectclass = Effect.GetRow<FGaMaEffectData>(TEXT("EffectData"))->
																	 EffectClass;
		FGameplayEffectSpecHandle Spec = AbilitySystemComponent->MakeOutgoingSpec(effectclass,1,EffectContext);
		if (Spec.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
		}
	}
}





