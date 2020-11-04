// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/GameInstanceSubsystem.h"
#include "AStarSearchSubsystem.generated.h"

class UAStarPathNode;
class UAStarSearchHeuristicCalculation;

/**
 * 
 */
UCLASS()
class ASTARSEARCHALGORITHM_API UAStarSearchSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category="AStarSearchAlgorithm")
    void FindPathTo( UAStarPathNode* Target, UAStarPathNode* Source, TArray<UAStarPathNode*>& OutPathList);
    
protected:
    void RelaxPath(UAStarPathNode* Node, UAStarPathNode* ParentNode);

    UAStarPathNode* PopHighestPriority(TArray<UAStarPathNode*> Nodes);

    int32 CalculatePriority(UAStarPathNode* Node, UAStarPathNode* Target, UAStarPathNode* Source);

    void PathList(UAStarPathNode* Target, TArray<UAStarPathNode*>& OutPathList);

private:
    
    uint32 bEnableRelax: 1;

    UPROPERTY()
    UAStarSearchHeuristicCalculation* HeuristicCalculation;
};
