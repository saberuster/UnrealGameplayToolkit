// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AStarSearchHeuristicCalculation.h"
#include "EuclideanHeuristicCalculation.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UEuclideanHeuristicCalculation : public UAStarSearchHeuristicCalculation
{
    GENERATED_BODY()

public:
    virtual void Calculate_Implementation(const FAStarSearchHeuristicParameters& Parameters,
                                          FAStarSearchHeuristicOutput& Output) const override;
};
