// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FAStarPathNode
{
    FAStarPathNode(): X(0), Y(0), HeuristicCost(0), BaseCost(MAX_int32), Parent(nullptr), D(MAX_int32)
    {
    }

public:

    int32 X;

    int32 Y;

    int32 HeuristicCost;

    int32 BaseCost;

    TSharedPtr<FAStarPathNode> Parent;

    int32 Priority;

    TArray<TSharedPtr<FAStarPathNode>> ConnectNodes;


    int32 Cost() const
    {
        return BaseCost + HeuristicCost;
    }


    friend bool operator==(const FAStarPathNode& Lhs, const FAStarPathNode& Rhs)
    {
        return Lhs.X == Rhs.X
            && Lhs.Y == Rhs.Y;
    }

    friend bool operator!=(const FAStarPathNode& Lhs, const FAStarPathNode& Rhs)
    {
        return !(Lhs == Rhs);
    }
};


class ASTARSEARCHALGORITHM_API FAStarSearchAlgorithm
{
public:
    FAStarSearchAlgorithm()
    {
    }

    TArray<TSharedPtr<FAStarPathNode>> Nodes;

    TArray<TSharedPtr<FAStarPathNode>> OpenNodes;

    TArray<TSharedPtr<FAStarPathNode>> CloseNodes;

    uint32 bEnableRelax:1;

    void PathFind(TSharedPtr<FAStarPathNode> Source, TSharedPtr<FAStarPathNode> Target)
    {
        OpenNodes.Add(Target);
        while (OpenNodes.Num() > 0)
        {
            TSharedPtr<FAStarPathNode> Node = PriorityPop();
            if (Node == Target)
            {
                PathList(Node);
            }
            else
            {
                CloseNodes.Add(Node);
                TArray<TSharedPtr<FAStarPathNode>> Neighbors = NeighborNodes();
                for (TSharedPtr<FAStarPathNode> NeighborsNode : Neighbors)
                {
                    if (bEnableRelax)
                    {
                        Relax(Node, NeighborsNode);
                    }
                    if (!CloseNodes.Contains(NeighborsNode))
                    {
                        NeighborsNode->Priority = CalculatePriority(NeighborsNode);
                        OpenNodes.Add(NeighborsNode);
                    }
                }
            }
        }
    }

    int32 CalculatePriority(TSharedPtr<FAStarPathNode> Node)
    {
        int32 Priority = Node->BaseCost;

        TSharedPtr<FAStarPathNode> Parent = Node->Parent;
        while (Parent != nullptr)
        {
            Priority += Parent->BaseCost;
            Parent = Parent->Parent;
        }

        return Priority;
    }

    TArray<TSharedPtr<FAStarPathNode>> NeighborNodes()
    {
        return TArray<TSharedPtr<FAStarPathNode>>();
    }

    TArray<TSharedPtr<FAStarPathNode>> PathList(TSharedPtr<FAStarPathNode> Target)
    {
        TArray<TSharedPtr<FAStarPathNode>> PathNodes;
        PathNodes.Add(Target);
        TSharedPtr<FAStarPathNode> Parent = Target->Parent;
        while (Parent != nullptr)
        {
            PathNodes.Add(Parent);
            Parent = Parent->Parent;
        }

        return PathNodes;
    }

    TSharedPtr<FAStarPathNode> PriorityPop()
    {
        int32 HightestPriority = MAX_int32;
        int32 FindIndex = -1;
        TSharedPtr<FAStarPathNode> FindNode = nullptr;
        for (int32 i = 0; i < OpenNodes.Num(); ++i)
        {
            if (HightestPriority > OpenNodes[i]->Priority)
            {
                HightestPriority = OpenNodes[i]->Priority;
                FindIndex = i;
            }
        }
        if (FindIndex > -1)
        {
            FindNode = MoveTempIfPossible(OpenNodes[FindIndex]);
            OpenNodes.RemoveAt(FindIndex, 1);
        }

        return FindNode;
    }

    void Relax(TSharedPtr<FAStarPathNode> U, TSharedPtr<FAStarPathNode> V)
    {
        if (V->Priority > U->Priority + V->BaseCost)
        {
            V->Priority = U->Priority + V->BaseCost;
            V->Parent = U;
        }
    }
};
