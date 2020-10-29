// Copyright saberuster. All Rights Reserved.


#include "UGAssetManager.h"

UUGAssetManager& UUGAssetManager::Get()
{
	UUGAssetManager* Singleton = Cast<UUGAssetManager>(GEngine->AssetManager);
    
	if (Singleton)
	{
		return *Singleton;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Cannot use AssetManager if no AssetManagerClassName is defined!"));
		return *NewObject<UUGAssetManager>(); // never calls this
	}
}

void UUGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}
