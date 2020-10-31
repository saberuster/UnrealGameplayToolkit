// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnrealGameplayStatics.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGAMEPLAYTOOLKIT_API UUnrealGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="UG")
	static bool IsActorValidToNotify(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="UG")
	static bool SelectActor(AActor* Actor, AActor* SourceActor);

	UFUNCTION(BlueprintCallable, Category="UG")
	static bool DeSelectActor(AActor* Actor, AActor* SourceActor);

	UFUNCTION(BlueprintCallable, Category="UG")
	static bool IsSelectable(AActor* Actor);
	
};
