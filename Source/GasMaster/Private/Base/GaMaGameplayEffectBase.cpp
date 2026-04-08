// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GaMaGameplayEffectBase.h"

#include "DataTableEditorUtils.h"
#include "FileHelpers.h"
#include "GaMaLog.h"
#include "Data//GaMaEffectSetAsset.h"
#include "UObject/ObjectSaveContext.h"

FName UGaMaGameplayEffectBase::GetEffectName() const
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
void UGaMaGameplayEffectBase::PreSave(FObjectPreSaveContext SaveContext)
{
	Super::PreSave(SaveContext);
	AddToTable();
}

void UGaMaGameplayEffectBase::AddToTable()
{
	if (!IsValid(EffectTable))
	{
		UE_LOG(LogGasMaster,Warning, TEXT("Trying to add Effect to inavlid table"));
		return;
	}
	FGaMaEffectData EffectAsset = FGaMaEffectData();
	EffectAsset.EffectClass = this->GetClass();
	EffectAsset.DisplayName = FText::FromName(GetEffectName());
	FString Name =EffectAsset.DisplayName.ToString();
	FDataTableEditorUtils::BroadcastPreChange(EffectTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
	EffectTable->AddRow(GetEffectName(),EffectAsset);
	bool success = EffectTable->Modify();
	if (success)
	{
		UE_LOG(LogGasMaster,Warning, TEXT("Added Effect to table: %s"), *Name);
	}
	else
	{
		UE_LOG(LogGasMaster,Warning, TEXT("Could not add Effect to table: %s"), *Name);
	}
	UEditorLoadingAndSavingUtils::SavePackages({EffectTable->GetPackage()}, false);
	FDataTableEditorUtils::BroadcastPostChange(EffectTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
	
}
#endif