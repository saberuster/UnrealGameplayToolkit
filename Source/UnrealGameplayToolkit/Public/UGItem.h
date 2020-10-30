// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UGItem.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGAMEPLAYTOOLKIT_API UUGItem : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:

    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Item")
    FPrimaryAssetType ItemType;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Item")
    FText ItemName;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Item")
    FText ItemDescription;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Item")
    FSlateBrush ItemIcon;


    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
