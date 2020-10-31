// Copyright saberuster. All Rights Reserved.


#include "UnrealGameplayStatics.h"

#include "UGActor.h"
#include "UGPawn.h"

bool UUnrealGameplayStatics::IsActorValidToNotify(AActor* Actor)
{
    return (Actor != nullptr) && !Actor->IsPendingKill() && !Actor->GetClass()->HasAnyClassFlags(
        CLASS_NewerVersionExists);
}

bool UUnrealGameplayStatics::SelectActor(AActor* Actor, AActor* SourceActor)
{
    if (IsActorValidToNotify(Actor))
    {
        AUGActor* UGActor = Cast<AUGActor>(Actor);
        if (UGActor)
        {
            if (IsActorValidToNotify(UGActor))
            {
                UGActor->NotifyUGActorOnSelected(SourceActor);
                if (IsActorValidToNotify(UGActor))
                {
                    UGActor->OnSelected.Broadcast(SourceActor);
                }
                return true;
            }
        }

        AUGPawn* UGPawn = Cast<AUGPawn>(Actor);
        if (UGPawn)
        {
            if (IsActorValidToNotify(UGPawn))
            {
                UGActor->NotifyUGActorOnSelected(SourceActor);
                if (IsActorValidToNotify(UGPawn))
                {
                    UGActor->OnSelected.Broadcast(SourceActor);
                }
                return true;
            }
        }

        if (IsSelectable(Actor))
        {
            if (IsActorValidToNotify(Actor))
            {
                IUGSelectableInterface* SelectableActor = Cast<IUGSelectableInterface>(Actor);
                SelectableActor->NotifyUGActorOnSelected(SourceActor);
                return true;
            }
        }
    }
    return false;
}

bool UUnrealGameplayStatics::DeSelectActor(AActor* Actor, AActor* SourceActor)
{
    if (IsActorValidToNotify(Actor))
    {
        AUGActor* UGActor = Cast<AUGActor>(Actor);
        if (UGActor)
        {
            if (IsActorValidToNotify(UGActor))
            {
                UGActor->NotifyUGActorOnDeSelected(SourceActor);
                if (IsActorValidToNotify(UGActor))
                {
                    UGActor->OnDeSelected.Broadcast(SourceActor);
                }
                return true;
            }
        }

        AUGPawn* UGPawn = Cast<AUGPawn>(Actor);
        if (UGPawn)
        {
            if (IsActorValidToNotify(UGPawn))
            {
                UGActor->NotifyUGActorOnSelected(SourceActor);
                if (IsActorValidToNotify(UGPawn))
                {
                    UGActor->OnDeSelected.Broadcast(SourceActor);
                }
                return true;
            }
        }

        if (IsSelectable(Actor))
        {
            if (IsActorValidToNotify(Actor))
            {
                IUGSelectableInterface* SelectableActor = Cast<IUGSelectableInterface>(Actor);
                SelectableActor->NotifyUGActorOnDeSelected(SourceActor);
                return true;
            }
        }
    }
    return false;
}

bool UUnrealGameplayStatics::IsSelectable(AActor* Actor)
{
    if (Actor)
    {
        return Actor->GetClass()->ImplementsInterface(UUGSelectableInterface::StaticClass());
    }

    return false;
}
