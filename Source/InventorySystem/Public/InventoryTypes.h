// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "InventoryTypes.generated.h"

class UUGItem;

USTRUCT(BlueprintType)
struct FUGItemSlot
{
    GENERATED_BODY()

    FUGItemSlot(): SlotNumber(-1)
    {
    }

    FUGItemSlot(const FPrimaryAssetType& InPrimaryAssetType, int32 InSlotNumber): SlotItemType(InPrimaryAssetType),
        SlotNumber(InSlotNumber)
    {
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    FPrimaryAssetType SlotItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    int32 SlotNumber;

    bool operator==(const FUGItemSlot& Other) const
    {
        return SlotItemType == Other.SlotItemType && SlotNumber == Other.SlotNumber;
    }

    bool operator !=(const FUGItemSlot& Other) const
    {
        return !(Other == *this);
    }

    friend inline uint32 GetTypeHash(const FUGItemSlot& In)
    {
        uint32 Hash = 0;
        Hash = HashCombine(Hash, GetTypeHash(In.SlotItemType));
        Hash = HashCombine(Hash, static_cast<uint32>(In.SlotNumber));

        return Hash;
    }

    bool IsValid() const
    {
        return SlotItemType.IsValid() && SlotNumber > 0;
    }
};

USTRUCT(BlueprintType)
struct FUGItemData
{
    GENERATED_BODY()

    FUGItemData(): ItemCount(0)
    {
    }

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Inventory")
    int32 ItemCount;

    FUGItemData& operator+(const FUGItemData& Other)
    {
        ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 0, MAX_int32);
        return *this;
    }


    bool IsValid() const
    {
        return ItemCount > 0;
    }
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryItemChanged, UUGItem*, ChangedItem);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryItemChangedNative, UUGItem*);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventorySlottedItemChanged, FUGItemSlot, ItemSlot, UUGItem*, Item);

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventorySlottedItemChangedNative, FUGItemSlot, UUGItem*);
