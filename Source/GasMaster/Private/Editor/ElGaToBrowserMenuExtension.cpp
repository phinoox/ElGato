// Fill out your copyright notice in the Description page of Project Settings.

#define LOCTEXT_NAMESPACE "FElGaToModule"
#include "Editor/ElGaToBrowserMenuExtension.h"

#include "ContentBrowserItemPath.h"
#include "ContentBrowserMenuContexts.h"
#include "EngineUtils.h"
#include "GaToLog.h"
#include "Base/GaToGameplayAbilityBase.h"
#include "Editor/AbilityEditorSubsystem.h"


void FElGaToBrowserMenuExtension::Init()
{
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FElGaToBrowserMenuExtension::RegisterMenus));
}



void FElGaToBrowserMenuExtension::RegisterMenus()
{
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("ContentBrowser.FolderContextMenu");
    
	if (Menu)
	{
		FText MenuLabel = FText::FromString(TEXT("ElGaTo"));
		
		// Add a new section or use an existing one (e.g., "AssetContextMoveActions")
		FToolMenuSection& Section = Menu->AddSection("ElGaTo", INVTEXT("My Custom Section"));
		 
		//auto SubMenu = Section.AddSubMenu(Menu->MenuOwner,"ElGaTo","ElGaTo",Label,Label);
		FToolMenuEntry SubMenu = Section.AddSubMenu(
			FName("ElGato"),
			MenuLabel,
			MenuLabel,
			FNewToolMenuDelegate::CreateRaw(this,&FElGaToBrowserMenuExtension::AddMenuEntry),
			false);
		
		
	
	}
}

void FElGaToBrowserMenuExtension::AddMenuEntry(UToolMenu* Menu)
{
	
	FToolMenuSection& AbilitySection = Menu->AddSection(FName("Abilities"),LOCTEXT("Abilities","ElGaTo"));
	UContentBrowserFolderContext* MenuContext = Menu->FindContext<UContentBrowserFolderContext>();
	UContentBrowserFolderContext* SectionContext = AbilitySection.FindContext<UContentBrowserFolderContext>();	//this always seems to be null
			FUIAction Action(
						FExecuteAction::CreateLambda([MenuContext,SectionContext]()
						{
							UContentBrowserFolderContext* Context;
							if (MenuContext)
							{
								Context = MenuContext;
							}
							else if (SectionContext)
							{
								Context = SectionContext;
							}
							else
							{
								UE_LOG(LogTemp, Log, TEXT("Custom action triggered but context was null"));
								return;
							}
							const TArray<FString>& SelectedPaths = Context->GetSelectedPackagePaths();
							for (auto Path : SelectedPaths)
							{
								TArray<UObject*> AbilityAssets;
								EngineUtils::FindOrLoadAssetsByPath(Path, AbilityAssets, EngineUtils::ATL_Regular);
								
								for (auto asset : AbilityAssets)
								{
									UGaToGameplayAbilityBase* AbilityBase = Cast<UGaToGameplayAbilityBase>(asset);
									if (AbilityBase != nullptr)
									{
										
									}
								}
							}
						}),
						FCanExecuteAction()
					);
			
			AbilitySection.AddEntry(
		FToolMenuEntry::InitMenuEntry(
					   FName("MyCustomAction"),
					   INVTEXT("My Custom Entry"),
					   INVTEXT("Tooltip for my custom entry"),
					   FSlateIcon(),
					   Action)
					   );
	
}

void FElGaToBrowserMenuExtension::OnCreateDataTables_Clicked()
{
}

#undef LOCTEXT_NAMESPACE
