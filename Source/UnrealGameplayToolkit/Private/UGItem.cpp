// Copyright saberuster. All Rights Reserved.


#include "UGItem.h"

FPrimaryAssetId UUGItem::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(ItemType, GetFName());
}
