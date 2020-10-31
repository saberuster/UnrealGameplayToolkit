// Copyright saberuster. All Rights Reserved.


#include "UGPawn.h"

// Sets default values
AUGPawn::AUGPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AUGPawn::NotifyUGActorOnSelected(AActor* SourceActor)
{
	ReceiveUGActorOnSelected(SourceActor);
}

void AUGPawn::NotifyUGActorOnDeSelected(AActor* SourceActor)
{
	ReceiveUGActorOnDeSelected(SourceActor);
}

// Called when the game starts or when spawned
void AUGPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUGPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUGPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

