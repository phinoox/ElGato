// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GaToGameplayAbilityBase.h"

#include "DataTableEditorUtils.h"
#include "ElGaToConfig.h"
#include "FileHelpers.h"
#include "GaToLog.h"
#include "Data/GaToAbilitySetAsset.h"
#include "Editor/AbilityAssetEditorFunctionLibrary.h"
#include "Editor/AbilityEditorSubsystem.h"
#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"
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
	UStringTable* StringTableAsset = AbilityEditorSubsystem->GetAbilityStringTable();
	
	if (!IsValid(AbilityTable))
	{
		UE_LOG(LogGaTo,Warning, TEXT("Trying to add ability to inavlid table"));
		return;
	}
	FGaToAbilityData AbilityAsset = FGaToAbilityData();
	AbilityAsset.AbilityClass = this->GetClass();
	
	FName AbilityName = GetAbilityName();
	
	AbilityAsset.DisplayName = FText::FromName(AbilityName);
	if (StringTableAsset)
	{
		FStringTableRef StringTable = StringTableAsset->GetMutableStringTable();
		FStringTableEntryConstPtr Entry = StringTable->FindEntry(AbilityName.ToString());
		const FString SourceString = AbilityName.ToString();
		
		if (!Entry.IsValid() || !Entry->GetSourceString().Equals(SourceString))
		{
			StringTableAsset->Modify();
			StringTable->SetSourceString(SourceString,SourceString);
			UAbilityAssetEditorFunctionLibrary::SaveAsset(StringTableAsset);
		}
		FName TableName = FName(StringTableAsset->GetName());
		//just using the assetname of the string table didn't do it, we need the path name
		AbilityAsset.DisplayName = FText::FromStringTable(FName(StringTableAsset->GetPathName()),SourceString);
	}
	
	FString Name =AbilityAsset.DisplayName.ToString();
	FDataTableEditorUtils::BroadcastPreChange(AbilityTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
	AbilityTable->AddRow(GetAbilityName(),AbilityAsset);
	if (bool success = AbilityTable->Modify())
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
