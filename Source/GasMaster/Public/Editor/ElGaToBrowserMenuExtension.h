// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

/**
 * 
 */

class ELGATO_API FElGaToBrowserMenuExtension : public TSharedFromThis<FElGaToBrowserMenuExtension>
{

public:
	void RegisterMenus();
	//FElGaToBrowserMenuExtension(const TArray<FString>&Path);
	void Init();
	void AddMenuEntry(UToolMenu* Menu);
	void FillSubMenu(FMenuBuilder& MenuBuilder);
	void OnCreateDataTables_Clicked();
private:
	TArray<FString> Path;
};
