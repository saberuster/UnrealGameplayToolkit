// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class IAStarCoordinate
{
public:
    virtual ~IAStarCoordinate() = default;
    virtual bool Equals(const IAStarCoordinate& Other) const = 0;

    friend bool operator==(const IAStarCoordinate& Lhs, const IAStarCoordinate& RHS)
    {
        return Lhs.Equals(RHS);
    }

    friend bool operator!=(const IAStarCoordinate& Lhs, const IAStarCoordinate& RHS)
    {
        return !(Lhs == RHS);
    }
};


class FAStarCoordinate2D : public IAStarCoordinate
{
public:

    FAStarCoordinate2D(): X(-1), Y(-1)
    {
    }

    FAStarCoordinate2D(int32 InX, int32 InY): X(InX), Y(InY)
    {
    }

    int32 X;

    int32 Y;

    virtual bool Equals(const IAStarCoordinate& Other) const override
    {
        const FAStarCoordinate2D* StarCoordinate2D = static_cast<const FAStarCoordinate2D*>(&Other);
        if (StarCoordinate2D)
        {
            return X == StarCoordinate2D->X && Y == StarCoordinate2D->Y;
        }
        return false;
    }
};


class FAStarPathNode
{
    FAStarPathNode():Parent(nullptr)
    {
    }

public:

    TSharedPtr<IAStarCoordinate> Coordinate;

    TArray<TSharedPtr<FAStarPathNode>> ConnectNodes;
    
    int32 Cost;

    TSharedPtr<FAStarPathNode> Parent;

    int32 Priority;

    bool IsSameCoordinate(const FAStarPathNode& Other) const
    {
        return Coordinate == Other.Coordinate;
    }


    friend bool operator==(const FAStarPathNode& Lhs, const FAStarPathNode& RHS)
    {
        return Lhs.IsSameCoordinate(RHS);
    }

    friend bool operator!=(const FAStarPathNode& Lhs, const FAStarPathNode& RHS)
    {
        return !(Lhs == RHS);
    }
};

class IAStarSearchAlgorithm
{
public:
    virtual ~IAStarSearchAlgorithm() = default;
};


class ASTARSEARCHALGORITHM_API FAStarSearchAlgorithm: public IAStarSearchAlgorithm
{
public:
    typedef TSharedPtr<FAStarPathNode> FPathNodePtr;
    typedef TArray<FPathNodePtr> FPathNodeCollection;
    
    FAStarSearchAlgorithm():bEnableRelax(true){}

    FPathNodeCollection Nodes;

    uint32 bEnableRelax:1;

    void FindPath(FPathNodePtr Source, FPathNodePtr Target, FPathNodeCollection& OutPathList)
    {
        FPathNodeCollection OpenNodes,CloseNodes;
        OpenNodes.Add(Source);
        while (OpenNodes.Num() > 0)
        {
            FPathNodePtr Node = PriorityPop(OpenNodes);
            if (Node == Target)
            {
                PathList(Node, OutPathList);
            }
            else
            {
                CloseNodes.Add(Node);
                for (FPathNodePtr NeighborsNode : Node->ConnectNodes)
                {
                    NeighborsNode->Priority = CalculatePriority(NeighborsNode);
                    if (bEnableRelax)
                    {
                        Relax(Node, NeighborsNode);
                    }
                    if (!CloseNodes.Contains(NeighborsNode))
                    {
                        OpenNodes.Add(NeighborsNode);
                    }
                }
            }
        }
    }

    void FindRadius(FPathNodePtr Source, int32 Radius, FPathNodeCollection& OutPathList)
    {
    }

    virtual int32 CalculatePriority(FPathNodePtr Node)
    {
        int32 Priority = Node->Cost;

        FPathNodePtr Parent = Node->Parent;
        while (Parent != nullptr)
        {
            Priority += Parent->Cost;
            Parent = Parent->Parent;
        }

        return Priority;
    }


    void PathList(FPathNodePtr Target,FPathNodeCollection& OutPathList)
    {
        FPathNodeCollection PathNodes;
        PathNodes.Add(Target);
        FPathNodePtr Parent = Target->Parent;
        while (Parent != nullptr)
        {
            PathNodes.Add(Parent);
            Parent = Parent->Parent;
        }
    }

    FPathNodePtr PriorityPop(FPathNodeCollection& OpenNodes)
    {
        int32 HightestPriority = MAX_int32;
        int32 FindIndex = -1;
        FPathNodePtr FindNode = nullptr;
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

    void Relax(FPathNodePtr U, FPathNodePtr V)
    {
        if (V->Priority > U->Priority + V->Cost)
        {
            V->Priority = U->Priority + V->Cost;
            V->Parent = U;
        }
    }
};
