// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/GaToGameplayEffectBase.h"

#include "DataTableEditorUtils.h"
#include "FileHelpers.h"
#include "GaToLog.h"
#include "Data//GaToEffectSetAsset.h"
#include "Editor/AbilityAssetEditorFunctionLibrary.h"
#include "Editor/AbilityEditorSubsystem.h"
#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"
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
	UAbilityEditorSubsystem* AbilityEditorSubsystem = GEditor->GetEditorSubsystem<UAbilityEditorSubsystem>();
	UDataTable* EffectTable = AbilityEditorSubsystem->GetEffectTable();
	UStringTable* StringTableAsset = AbilityEditorSubsystem->GetEffectStringTable();
	
	if (!IsValid(EffectTable))
	{
		UE_LOG(LogGaTo,Warning, TEXT("Trying to add Effect to inavlid table"));
		return;
	}
	FGaToEffectData EffectAsset = FGaToEffectData();
	EffectAsset.EffectClass = this->GetClass();
	FName EffectName = GetEffectName();
	EffectAsset.DisplayName = FText::FromName(EffectName);
	if (StringTableAsset)
	{
		FStringTableRef StringTable = StringTableAsset->GetMutableStringTable();
		FStringTableEntryConstPtr Entry = StringTable->FindEntry(EffectName.ToString());
		const FString SourceString = EffectName.ToString();
		
		if (!Entry.IsValid() || !Entry->GetSourceString().Equals(SourceString))
		{
			StringTableAsset->Modify();
			StringTable->SetSourceString(SourceString,SourceString);
			UAbilityAssetEditorFunctionLibrary::SaveAsset(StringTableAsset);
		}
		FName TableName = FName(StringTableAsset->GetName());
		//just using the assetname of the string table didn't do it, we need the path name
		EffectAsset.DisplayName = FText::FromStringTable(FName(StringTableAsset->GetPathName()),SourceString);
	}
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