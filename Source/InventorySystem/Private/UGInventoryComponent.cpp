// Copyright saberuster. All Rights Reserved.


#include "UGInventoryComponent.h"

// Sets default values for this component's properties
UUGInventoryComponent::UUGInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


bool UUGInventoryComponent::AddInventoryItem(UUGItem* Item, FUGItemData DeltaItemData)
{
	FUGItemData& ItemData = InventoryData.FindOrAdd(Item);
	ItemData = ItemData + DeltaItemData;
	OnInventoryItemChangedNative.Broadcast(Item);
	OnInventoryItemChanged.Broadcast(Item);
	return true;
}

bool UUGInventoryComponent::SetSlottedItem(FUGItemSlot ItemSlot, UUGItem* Item)
{
	SlottedItems.Add(ItemSlot, Item);
	OnInventorySlottedItemChangedNative.Broadcast(ItemSlot, Item);
	OnInventorySlottedItemChanged.Broadcast(ItemSlot, Item);
	return true;
}

UUGItem* UUGInventoryComponent::GetSlottedItem(FUGItemSlot ItemSlot)
{
	return SlottedItems[ItemSlot];
}

// Called when the game starts
void UUGInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUGInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

