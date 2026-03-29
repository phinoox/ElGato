// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/GaMaEffectSetAsset.h"

FGaMaEffectData UGaMaEffectSetAsset::GetEffectAssetByName(FText Name)
{
	for (auto EffectData : Effects)
	{
		FGaMaEffectData* effect = EffectData.GetRow<FGaMaEffectData>(TEXT("EffectData"));
		if (effect->DisplayName.EqualTo(Name))
		{
			return *effect;
		}
	}
	return FGaMaEffectData();
}

FGaMaEffectData UGaMaEffectSetAsset::GetEffectAssetByClass(TSubclassOf<UGaMaGameplayEffectBase> EffectClass)
{
	for (auto EffectData : Effects)
	{
		FGaMaEffectData* effect = EffectData.GetRow<FGaMaEffectData>(TEXT("EffectData"));
		if (effect->EffectClass == EffectClass)
		{
			return *effect;
		}
	}
	return FGaMaEffectData();
}
