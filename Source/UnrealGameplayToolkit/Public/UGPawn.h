// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/UGSelectableInterface.h"
#include "GameFramework/Pawn.h"
#include "UGPawn.generated.h"

class AUGPawn;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FUGPawnOnSelectedSignature, AUGPawn, OnSelected, AActor*, SourceActor);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FUGPawnOnDeSelectedSignature, AUGPawn, OnDeSelected, AActor*, SourceActor);

UCLASS()
class UNREALGAMEPLAYTOOLKIT_API AUGPawn : public APawn, public IUGSelectableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUGPawn();
	UPROPERTY(BlueprintAssignable, Category="UG")
	FUGPawnOnSelectedSignature OnSelected;
	
	UPROPERTY(BlueprintAssignable, Category="UG")
	FUGPawnOnDeSelectedSignature OnDeSelected;
	
	virtual void NotifyUGActorOnSelected(AActor* SourceActor) override;
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnSelected"), Category="UG")
	void ReceiveUGActorOnSelected(AActor* SourceActor);

	virtual void NotifyUGActorOnDeSelected(AActor* SourceActor) override;
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnDeSelected"), Category="UG")
	void ReceiveUGActorOnDeSelected(AActor* SourceActor);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
