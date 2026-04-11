// Copyright Epic Games, Inc. All Rights Reserved.

#include "ElGato.h"

#include "ContentBrowserMenuContexts.h"
#include "ContentBrowserModule.h"
#include "ElGaToSettings.h"
#include "GaToLog.h"
#include "GameplayTagsManager.h"
#include "IngestCaptureData.h"
#include "ISettingsModule.h"
#include "SBlueprintEditorToolbar.h"
#include "ToolMenus.h"
#include "Editor/ElGaToBrowserMenuExtension.h"
#include "Interfaces/IPluginManager.h"


#define LOCTEXT_NAMESPACE "FElGaToModule"


void FElGaToModule::StartupModule()
{
	FString BaseDir = IPluginManager::Get().FindPlugin(TEXT("ElGaTo"))->GetBaseDir();
	FString TagsIniDirectory = BaseDir / TEXT("Config") / TEXT("Tags");
	if (FPaths::DirectoryExists(TagsIniDirectory))
	{
			UE_LOG(LogGaTo, Log, TEXT("TagIniSearchPath: %s Added"), *TagsIniDirectory);

			UGameplayTagsManager::Get().AddTagIniSearchPath(TagsIniDirectory);
	}
	else
	{
			UE_LOG(LogGaTo, Warning, TEXT("TagIniSearchPath: %s not found"), *TagsIniDirectory);
	}
	RegisterSettings();
	Extension = MakeShareable(
	   new FElGaToBrowserMenuExtension());
	Extension->Init();
	//AddContentBrowserActions();
}


void FElGaToModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "ElGaTo_Settings");
	}
}

void FElGaToModule::RegisterSettings()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project",
			"Plugins",
			"ElGaTo_Settings",
			LOCTEXT("RuntimeSettingsName", "ElGaTo Settings"),
			LOCTEXT("RuntimeSettingsDescription", "Configure ElGaTo"),
			GetMutableDefault<UElGaToSettings>()
		);
	}
}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FElGaToModule, ElGaTo)