// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GaToAbilitySystemsGlobal.h"

#include "Base/GaToAtributeSetInitter.h"

void UGaToAbilitySystemsGlobal::AllocAttributeSetInitter()
{
	//Super::AllocAttributeSetInitter();
	GlobalAttributeSetInitter = TSharedPtr<FGaToAtributeSetInitter>(new FGaToAtributeSetInitter());
}
