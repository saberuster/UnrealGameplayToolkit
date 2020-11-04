// Copyright Epic Games, Inc. All Rights Reserved.

#include "AStarPathNode.h"

UAStarPathNode::UAStarPathNode()
    : X(-1)
      , Y(-1)
      , Cost(1)
      , Priority(0)
{
}

bool UAStarPathNode::IsSameCoordinate(const UAStarPathNode& Other) const
{
    return X == Other.X && Y == Other.Y;
}

bool operator==(const UAStarPathNode& Lhs, const UAStarPathNode& RHS)
{
    return Lhs.IsSameCoordinate(RHS);
}

bool operator!=(const UAStarPathNode& Lhs, const UAStarPathNode& RHS)
{
    return !(Lhs == RHS);
}
