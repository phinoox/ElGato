// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/GaMaAbilitySetAsset.h"

#include "Base/GaMaGameplayAbilityBase.h"

FGaMaAbilityData UGaMaAbilitySetAsset::GetAbilityAssetByName(FText Name)
{
	for (auto AbilitiyData : Abilities)
	{
		FGaMaAbilityData* ability = AbilitiyData.GetRow<FGaMaAbilityData>(TEXT("AbilityData"));
		if (ability->DisplayName.EqualTo(Name))
		{
			return *ability;
		}
	}
	return FGaMaAbilityData();
}

FGaMaAbilityData UGaMaAbilitySetAsset::GetAbilityAssetByClass(
	TSubclassOf<UGaMaGameplayAbilityBase> AbilityClass)
{
	for (auto AbilitiyData : Abilities)
	{
		FGaMaAbilityData* ability = AbilitiyData.GetRow<FGaMaAbilityData>(TEXT("AbilityData"));
		if (ability->AbilityClass == AbilityClass)
		{
			return *ability;
		}
	}
	return FGaMaAbilityData();
}
