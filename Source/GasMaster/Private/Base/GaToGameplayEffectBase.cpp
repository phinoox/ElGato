// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GaToGameplayEffectBase.h"

#include "DataTableEditorUtils.h"
#include "FileHelpers.h"
#include "GaToLog.h"
#include "Data//GaToEffectSetAsset.h"
#include "UObject/ObjectSaveContext.h"

FName UGaToGameplayEffectBase::GetEffectName() const
{
	FString EffectName;
	EffectName = this->GetClass()->GetName();
	FString Left,Right;
	EffectName.Split("_",&Left,&EffectName);
	EffectName.Split("_",&EffectName,&Right,ESearchCase::CaseSensitive,ESearchDir::FromEnd);
	EffectName = EffectName.Replace(TEXT("_"),TEXT(""));
	return FName(*EffectName);
}

#if WITH_EDITOR
void UGaToGameplayEffectBase::PreSave(FObjectPreSaveContext SaveContext)
{
	Super::PreSave(SaveContext);
	AddToTable();
}

void UGaToGameplayEffectBase::AddToTable()
{
	if (!IsValid(EffectTable))
	{
		UE_LOG(LogGaTo,Warning, TEXT("Trying to add Effect to inavlid table"));
		return;
	}
	FGaToEffectData EffectAsset = FGaToEffectData();
	EffectAsset.EffectClass = this->GetClass();
	EffectAsset.DisplayName = FText::FromName(GetEffectName());
	FString Name =EffectAsset.DisplayName.ToString();
	FDataTableEditorUtils::BroadcastPreChange(EffectTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
	EffectTable->AddRow(GetEffectName(),EffectAsset);
	bool success = EffectTable->Modify();
	if (success)
	{
		UE_LOG(LogGaTo,Warning, TEXT("Added Effect to table: %s"), *Name);
	}
	else
	{
		UE_LOG(LogGaTo,Warning, TEXT("Could not add Effect to table: %s"), *Name);
	}
	UEditorLoadingAndSavingUtils::SavePackages({EffectTable->GetPackage()}, false);
	FDataTableEditorUtils::BroadcastPostChange(EffectTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
	
}
#endif