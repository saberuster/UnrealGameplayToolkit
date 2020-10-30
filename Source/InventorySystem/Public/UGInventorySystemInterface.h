// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "InventoryTypes.h"
#include "UObject/Interface.h"
#include "UGInventorySystemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUGInventorySystemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORYSYSTEM_API IUGInventorySystemInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual FOnInventoryItemChangedNative& GetInventoryItemChangedDelegate() = 0;

	virtual FOnInventorySlottedItemChangedNative& GetInventorySlottedItemChangedDelegate() = 0;
};
