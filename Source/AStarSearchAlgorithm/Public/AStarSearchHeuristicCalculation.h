// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AStarSearchHeuristicCalculation.generated.h"

class UAStarPathNode;

USTRUCT(BlueprintType)
struct ASTARSEARCHALGORITHM_API FAStarSearchHeuristicParameters
{
    GENERATED_BODY()
public:

    FAStarSearchHeuristicParameters(){}
    FAStarSearchHeuristicParameters(UAStarPathNode* InNode):Node(InNode){}
    FAStarSearchHeuristicParameters(UAStarPathNode* InNode, UAStarPathNode* InSource,UAStarPathNode* InTarget):Node(InNode),Source(InSource),Target(InTarget){}

    TWeakObjectPtr<UAStarPathNode> Node;
    TWeakObjectPtr<UAStarPathNode> Source;
    TWeakObjectPtr<UAStarPathNode> Target;
};


USTRUCT(BlueprintType)
struct ASTARSEARCHALGORITHM_API FAStarSearchHeuristicOutput
{
    GENERATED_BODY()
public:

    FAStarSearchHeuristicOutput(): OutPriority(0){}

    int32 OutPriority;
};


UCLASS(BlueprintType, Blueprintable)
class ASTARSEARCHALGORITHM_API UAStarSearchHeuristicCalculation : public UObject
{
    GENERATED_BODY()
public:

    UFUNCTION(BlueprintNativeEvent, Category="Calculation")
    void Calculate(const FAStarSearchHeuristicParameters& Parameters, FAStarSearchHeuristicOutput& Output) const;
    virtual void Calculate_Implementation(const FAStarSearchHeuristicParameters& Parameters, FAStarSearchHeuristicOutput& Output) const;
};