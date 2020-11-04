// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

ASTARSEARCHALGORITHM_API DECLARE_LOG_CATEGORY_EXTERN(LogAStarSearchAlgorithm, Log, All);

class FAStarSearchAlgorithmModule : public IModuleInterface
{
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
