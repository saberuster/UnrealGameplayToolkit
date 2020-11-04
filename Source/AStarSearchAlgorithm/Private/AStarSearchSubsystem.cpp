// Copyright saberuster. All Rights Reserved.

#include "AStarSearchSubsystem.h"
#include "AStarPathNode.h"
#include "UGDeveloperSettings.h"
#include "AStarSearchHeuristicCalculation.h"


void UAStarSearchSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    
    bEnableRelax = GetDefault<UUGDeveloperSettings>()->bEnableRelax;
    
    UClass* HeuristicCalculationClass;
    if(GetDefault<UUGDeveloperSettings>()->DefaultHeuristicCalculationClass.IsValid())
    {
        HeuristicCalculationClass = LoadObject<UClass>(this,*GetDefault<UUGDeveloperSettings>()->DefaultHeuristicCalculationClass.ToString());
    }else
    {
        HeuristicCalculationClass = UAStarSearchHeuristicCalculation::StaticClass();   
    }
    HeuristicCalculation = NewObject<UAStarSearchHeuristicCalculation>(this, HeuristicCalculationClass);
}

void UAStarSearchSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

void UAStarSearchSubsystem::FindPathTo(UAStarPathNode* Target, UAStarPathNode* Source,
                                       TArray<UAStarPathNode*>& OutPathList)
{
    static TArray<UAStarPathNode*> OpenNodes, CloseNodes;
    checkf(IsValid(Target), TEXT("UAStarSearchSubsystem: Target is Invalid!"));
    checkf(IsValid(Source), TEXT("UAStarSearchSubsystem: Source is Invalid!"));

    OpenNodes.Add(Source);

    while (OpenNodes.Num() > 0)
    {
        UAStarPathNode* Node = PopHighestPriority(OpenNodes);
        checkf(Node, TEXT("Node is invalid"));
        if (*Node == *Target)
        {
            PathList(Target, OutPathList);
        }
        else
        {
            Node->Priority = CalculatePriority(Node,Target,Source);
            for (TWeakObjectPtr<UAStarPathNode> ChildNode : Node->ConnectNodes)
            {
                checkf(ChildNode.IsValid(), TEXT("childNode is invalid"));
                if (bEnableRelax)
                {
                    RelaxPath(ChildNode.Get(), Node);
                }
                if (!CloseNodes.Contains(ChildNode))
                {
                    OpenNodes.Add(ChildNode.Get());
                }
            }
        }
    }


    OpenNodes.Reset();
    CloseNodes.Reset();
}

void UAStarSearchSubsystem::RelaxPath(UAStarPathNode* Node, UAStarPathNode* ParentNode)
{
    if (Node->Priority > ParentNode->Priority + Node->Cost)
    {
        Node->Priority = ParentNode->Priority + Node->Cost;
        Node->Parent = ParentNode;
    }
}

UAStarPathNode* UAStarSearchSubsystem::PopHighestPriority(TArray<UAStarPathNode*> Nodes)
{
    int32 HightestPriority = MAX_int32;
    int32 FindIndex = INDEX_NONE;
    UAStarPathNode* FindNode = nullptr;
    for (int32 i = 0; i < Nodes.Num(); ++i)
    {
        if (HightestPriority > Nodes[i]->Priority)
        {
            HightestPriority = Nodes[i]->Priority;
            FindIndex = i;
        }
    }
    if (FindIndex > INDEX_NONE)
    {
        FindNode = Nodes[FindIndex];
        Nodes.RemoveAt(FindIndex, 1);
    }

    return FindNode;
}

int32 UAStarSearchSubsystem::CalculatePriority(UAStarPathNode* Node,UAStarPathNode* Target, UAStarPathNode* Source)
{
    int32 Priority = Node->Cost;

    TWeakObjectPtr<UAStarPathNode> Parent = Node->Parent;
    while (Parent.IsValid())
    {
        Priority += Parent->Cost;
        Parent = Parent->Parent;
    }

    const FAStarSearchHeuristicParameters Parameters(Node, Source, Target);
    FAStarSearchHeuristicOutput Output;
    HeuristicCalculation->Calculate(Parameters, Output);
    Priority += Output.OutPriority;
    return Priority;
}

void UAStarSearchSubsystem::PathList(UAStarPathNode* Target, TArray<UAStarPathNode*>& OutPathList)
{
    OutPathList.Add(Target);
    TWeakObjectPtr<UAStarPathNode> Parent = Target->Parent;
    while (Parent.IsValid())
    {
        OutPathList.Add(Parent.Get());
        Parent = Parent->Parent;
    }
}
