// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AStarPathNode.generated.h"

UCLASS()
class ASTARSEARCHALGORITHM_API UAStarPathNode: public UObject
{
    GENERATED_BODY()
public:
    UAStarPathNode();

    UPROPERTY()
    int32 X;

    UPROPERTY()
    int32 Y;

    UPROPERTY()
    int32 Cost;

    UPROPERTY()
    TWeakObjectPtr<UAStarPathNode> Parent;

    UPROPERTY()
    TArray<TWeakObjectPtr<UAStarPathNode>> ConnectNodes;

    UPROPERTY(Transient)
    int32 Priority;

    bool IsSameCoordinate(const UAStarPathNode& Other) const;


    friend bool operator==(const UAStarPathNode& Lhs, const UAStarPathNode& RHS);
    friend bool operator!=(const UAStarPathNode& Lhs, const UAStarPathNode& RHS);
    
};

