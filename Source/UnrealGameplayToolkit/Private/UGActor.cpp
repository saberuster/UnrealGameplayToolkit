// Copyright saberuster. All Rights Reserved.


#include "UGActor.h"

#include "UnrealGameplayStatics.h"

void AUGActor::NotifyUGActorOnSelected(AActor* SourceActor)
{
    ReceiveUGActorOnSelected(SourceActor);
}

void AUGActor::NotifyUGActorOnDeSelected(AActor* SourceActor)
{
    ReceiveUGActorOnDeSelected(SourceActor);
}

// Sets default values
AUGActor::AUGActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUGActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AUGActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
