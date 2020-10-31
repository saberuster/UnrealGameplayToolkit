// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UGSelectableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUGSelectableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREALGAMEPLAYTOOLKIT_API IUGSelectableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void NotifyUGActorOnSelected(AActor* SourceActor) = 0;
	
	virtual void NotifyUGActorOnDeSelected(AActor* SourceActor) = 0;
};
