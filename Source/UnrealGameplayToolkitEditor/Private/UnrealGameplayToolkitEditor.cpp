// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealGameplayToolkitEditor.h"


#include "GameplayCreationMenu.h"
#include "ISettingsModule.h"

#define LOCTEXT_NAMESPACE "FUnrealGameplayToolkitEditorModule"

class FUnrealGameplayToolkitEditorModule : public IUnrealGameplayToolkitEditorModule
{
    virtual void StartupModule() override
    {
        FCoreDelegates::OnPostEngineInit.AddRaw(this, &FUnrealGameplayToolkitEditorModule::OnPostEngineInit);
    }

    void OnPostEngineInit()
    {
        if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
        {
           SettingsModule->RegisterSettings(
               "Project","Plugins","UnrealGameplayToolkitEditor",
               NSLOCTEXT("FUnrealGameplayToolkitEditorModule","UnrealGameplayToolkitName", "UnrealGameplayToolkitEditor"),
               NSLOCTEXT("FUnrealGameplayToolkitEditorModule","UnrealGameplayToolkitDesc", "UnrealGameplayToolkitEditor settings"),
               GetMutableDefault<UGameplayCreationMenu>()
               );

            GetDefault<UGameplayCreationMenu>()->AddMenuExtensions();
        }
    }


    virtual void ShutdownModule() override
    {
    }
};

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FUnrealGameplayToolkitEditorModule, UnrealGameplayToolkitEditor)
