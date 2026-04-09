// Copyright Epic Games, Inc. All Rights Reserved.

#include "ElGato.h"

#include "GaToLog.h"
#include "GameplayTagsManager.h"
#include "Interfaces/IPluginManager.h"


#define LOCTEXT_NAMESPACE "FGasMasterModule"


void FGasMasterModule::StartupModule()
{
	FString BaseDir = IPluginManager::Get().FindPlugin(TEXT("GasMaster"))->GetBaseDir();
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
}


void FGasMasterModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGasMasterModule, GasMaster)