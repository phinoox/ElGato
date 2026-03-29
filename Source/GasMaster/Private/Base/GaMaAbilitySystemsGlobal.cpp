// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GaMaAbilitySystemsGlobal.h"

#include "Base/GaMaAtributeSetInitter.h"

void UGaMaAbilitySystemsGlobal::AllocAttributeSetInitter()
{
	//Super::AllocAttributeSetInitter();
	GlobalAttributeSetInitter = TSharedPtr<FGaMaAtributeSetInitter>(new FGaMaAtributeSetInitter());
}
