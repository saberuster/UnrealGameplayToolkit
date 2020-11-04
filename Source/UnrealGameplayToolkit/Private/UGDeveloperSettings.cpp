// Copyright saberuster. All Rights Reserved.


#include "UGDeveloperSettings.h"


UUGDeveloperSettings::UUGDeveloperSettings()
    :bEnableRelax(false)
    ,DefaultHeuristicCalculationClass(TEXT(""))
{
}

FName UUGDeveloperSettings::GetCategoryName() const
{
    return TEXT("Plugins");
}
