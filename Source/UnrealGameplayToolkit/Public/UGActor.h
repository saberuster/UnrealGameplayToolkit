// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/UGSelectableInterface.h"
#include "GameFramework/Actor.h"
#include "UGActor.generated.h"

class AUGActor;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FUGActorOnSelectedSignature, AUGActor, OnSelected, AActor*, SourceActor);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FUGActorOnDeSelectedSignature, AUGActor, OnDeSelected, AActor*, SourceActor);

/**
 * add OnSelected and OnDeSelected
 */
UCLASS()
class UNREALGAMEPLAYTOOLKIT_API AUGActor : public AActor, public IUGSelectableInterface
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable, Category="UG")
	FUGActorOnSelectedSignature OnSelected;
	
	UPROPERTY(BlueprintAssignable, Category="UG")
	FUGActorOnDeSelectedSignature OnDeSelected;
	
	//void DispatchOnSelected(AActor* SourceActor);
	virtual void NotifyUGActorOnSelected(AActor* SourceActor) override;
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnSelected"), Category="UG")
	void ReceiveUGActorOnSelected(AActor* SourceActor);

	//void DispatchOnDeSelected(AActor* SourceActor);
	virtual void NotifyUGActorOnDeSelected(AActor* SourceActor) override;
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="OnDeSelected"), Category="UG")
	void ReceiveUGActorOnDeSelected(AActor* SourceActor);

	
	// Sets default values for this actor's properties
	AUGActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
