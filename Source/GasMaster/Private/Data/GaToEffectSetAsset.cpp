// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/GaToEffectSetAsset.h"

FGaToEffectData UGaToEffectSetAsset::GetEffectAssetByName(FText Name)
{
	for (auto EffectData : Effects)
	{
		FGaToEffectData* effect = EffectData.GetRow<FGaToEffectData>(TEXT("EffectData"));
		if (effect->DisplayName.EqualTo(Name))
		{
			return *effect;
		}
	}
	return FGaToEffectData();
}

FGaToEffectData UGaToEffectSetAsset::GetEffectAssetByClass(TSubclassOf<UGaToGameplayEffectBase> EffectClass)
{
	for (auto EffectData : Effects)
	{
		FGaToEffectData* effect = EffectData.GetRow<FGaToEffectData>(TEXT("EffectData"));
		if (effect->EffectClass == EffectClass)
		{
			return *effect;
		}
	}
	return FGaToEffectData();
}
