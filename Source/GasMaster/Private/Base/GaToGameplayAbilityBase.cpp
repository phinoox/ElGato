// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GaToGameplayAbilityBase.h"

#include "DataTableEditorUtils.h"
#include "FileHelpers.h"
#include "GaToLog.h"
#include "Data/GaToAbilitySetAsset.h"
#include "Editor/AbilityEditorSubsystem.h"
#include "UObject/ObjectSaveContext.h"

UGaToGameplayAbilityBase::UGaToGameplayAbilityBase()
{

}

FName UGaToGameplayAbilityBase::GetAbilityName() const
{
	FString AbilityName;
	AbilityName = this->GetClass()->GetName();
	FString Left,Right;
	AbilityName.Split("_",&Left,&AbilityName);
	AbilityName.Split("_",&AbilityName,&Right,ESearchCase::CaseSensitive,ESearchDir::FromEnd);
	AbilityName = AbilityName.Replace(TEXT("_"),TEXT(""));
	return FName(*AbilityName);
}

#if WITH_EDITOR
void UGaToGameplayAbilityBase::AddToTable()
{
	UAbilityEditorSubsystem* AbilityEditorSubsystem = GEditor->GetEditorSubsystem<UAbilityEditorSubsystem>();
	UDataTable* AbilityTable = AbilityEditorSubsystem->GetAbilityTable();
	if (!IsValid(AbilityTable))
	{
		UE_LOG(LogGaTo,Warning, TEXT("Trying to add ability to inavlid table"));
		return;
	}
	FGaToAbilityData AbilityAsset = FGaToAbilityData();
	AbilityAsset.AbilityClass = this->GetClass();
	AbilityAsset.DisplayName = FText::FromName(GetAbilityName());
	FString Name =AbilityAsset.DisplayName.ToString();
	FDataTableEditorUtils::BroadcastPreChange(AbilityTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
	AbilityTable->AddRow(GetAbilityName(),AbilityAsset);
	bool success = AbilityTable->Modify();
	if (success)
	{
		UE_LOG(LogGaTo,Warning, TEXT("Added ability to table: %s"), *Name);
	}
	else
	{
		UE_LOG(LogGaTo,Warning, TEXT("Could not add ability to table: %s"), *Name);
	}
	UEditorLoadingAndSavingUtils::SavePackages({AbilityTable->GetPackage()}, false);
	FDataTableEditorUtils::BroadcastPostChange(AbilityTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
}


void UGaToGameplayAbilityBase::PreSave(FObjectPreSaveContext SaveContext)
{
	Super::PreSave(SaveContext);
	AddToTable();
}
#endif		
