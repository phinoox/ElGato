// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GaMaGameplayAbilityBase.h"

#include "DataTableEditorUtils.h"
#include "FileHelpers.h"
#include "Data/GaMaAbilitySetAsset.h"
#include "UObject/ObjectSaveContext.h"

FName UGaMaGameplayAbilityBase::GetAbilityName() const
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
void UGaMaGameplayAbilityBase::AddToTable()
{
	if (!IsValid(AbilityTable))
	{
		UE_LOG(LogTemp,Warning, TEXT("Trying to add ability to inavlid table"));
		return;
	}
	FGaMaAbilityData AbilityAsset = FGaMaAbilityData();
	AbilityAsset.AbilityClass = this->GetClass();
	AbilityAsset.DisplayName = FText::FromName(GetAbilityName());
	FString Name =AbilityAsset.DisplayName.ToString();
	FDataTableEditorUtils::BroadcastPreChange(AbilityTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
	AbilityTable->AddRow(GetAbilityName(),AbilityAsset);
	bool success = AbilityTable->Modify();
	if (success)
	{
		UE_LOG(LogTemp,Warning, TEXT("Added ability to table: %s"), *Name);
	}
	else
	{
		UE_LOG(LogTemp,Warning, TEXT("Could not add ability to table: %s"), *Name);
	}
	UEditorLoadingAndSavingUtils::SavePackages({AbilityTable->GetPackage()}, false);
	FDataTableEditorUtils::BroadcastPostChange(AbilityTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
	
	//DataTable->MarkPackageDirty();
	//DataTable->PostEditChange();
}


void UGaMaGameplayAbilityBase::PreSave(FObjectPreSaveContext SaveContext)
{
	Super::PreSave(SaveContext);
	AddToTable();
}
#endif		
