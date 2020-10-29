// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "UGAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class UNREALGAMEPLAYTOOLKIT_API UUGAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UUGAssetManager& Get();

	virtual void StartInitialLoading() override;
};
