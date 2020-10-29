// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IUnrealGameplayToolkitEditorModule : public IModuleInterface
{
public:

    static inline IUnrealGameplayToolkitEditorModule& Get()
    {
        return FModuleManager::LoadModuleChecked<IUnrealGameplayToolkitEditorModule>("UnrealGameplayToolkitEditor");
    }

    /**
     * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
     *
     * @return True if the module is loaded and ready to use
     */
    static inline bool IsAvailable()
    {
        return FModuleManager::Get().IsModuleLoaded("UnrealGameplayToolkitEditor");
    }
};
