// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InventoryTypes.h"
#include "UGInventorySystemInterface.h"
#include "Components/ActorComponent.h"
#include "UGInventoryComponent.generated.h"

class UUGItem;


UCLASS( ClassGroup=(UG), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UUGInventoryComponent : public UActorComponent, public IUGInventorySystemInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UUGInventoryComponent();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory")
    TMap<FUGItemSlot, UUGItem*> SlottedItems;


    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory")
    TMap<UUGItem*, FUGItemData> InventoryData;


    UPROPERTY(BlueprintAssignable, Category="Inventory")
    FOnInventoryItemChanged OnInventoryItemChanged;
    FOnInventoryItemChangedNative OnInventoryItemChangedNative;

    UPROPERTY(BlueprintAssignable, Category="Inventory")
    FOnInventorySlottedItemChanged OnInventorySlottedItemChanged;
    FOnInventorySlottedItemChangedNative OnInventorySlottedItemChangedNative;

    virtual FOnInventoryItemChangedNative& GetInventoryItemChangedDelegate() override
    {
        return OnInventoryItemChangedNative;
    }

    virtual FOnInventorySlottedItemChangedNative& GetInventorySlottedItemChangedDelegate() override
    {
        return OnInventorySlottedItemChangedNative;
    }

    UFUNCTION(BlueprintCallable, Category="Inventory")
    bool AddInventoryItem(UUGItem* Item, FUGItemData DeltaItemData);

    UFUNCTION(BlueprintCallable, Category="Inventory")
    bool SetSlottedItem(FUGItemSlot ItemSlot, UUGItem* Item);

    UFUNCTION(BlueprintCallable, Category="Inventory")
    UUGItem* GetSlottedItem(FUGItemSlot ItemSlot);

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;
};
