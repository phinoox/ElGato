// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ContentBrowserDelegates.h"
#include "Modules/ModuleManager.h"

class FElGaToBrowserMenuExtension;

class FElGaToModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	void RegisterSettings();
	TSharedPtr<FElGaToBrowserMenuExtension> Extension;
};
