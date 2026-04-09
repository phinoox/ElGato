// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/GaToAbilitySetAsset.h"

#include "Base/GaToGameplayAbilityBase.h"

FGaToAbilityData UGaToAbilitySetAsset::GetAbilityAssetByName(FText Name)
{
	for (auto AbilitiyData : Abilities)
	{
		FGaToAbilityData* ability = AbilitiyData.GetRow<FGaToAbilityData>(TEXT("AbilityData"));
		if (ability->DisplayName.EqualTo(Name))
		{
			return *ability;
		}
	}
	return FGaToAbilityData();
}

FGaToAbilityData UGaToAbilitySetAsset::GetAbilityAssetByClass(
	TSubclassOf<UGaToGameplayAbilityBase> AbilityClass)
{
	for (auto AbilitiyData : Abilities)
	{
		FGaToAbilityData* ability = AbilitiyData.GetRow<FGaToAbilityData>(TEXT("AbilityData"));
		if (ability->AbilityClass == AbilityClass)
		{
			return *ability;
		}
	}
	return FGaToAbilityData();
}
