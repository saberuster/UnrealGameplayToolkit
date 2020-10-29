// Copyright saberuster. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "GameplayCreationMenu.generated.h"

USTRUCT()
struct FGameplayCreationData
{
    GENERATED_BODY()
	/** Where to show this in the menu. Use "|" for sub categories. E.g, "Status|Hard|Stun|Root". */
	UPROPERTY(EditAnywhere, Category="Menu Path")
	FString MenuPath;

	/** The default name of the new asset. E.g "BP_Test" -> GA_Damage or GA_HeroName_AbilityName_Damage */
	UPROPERTY(EditAnywhere, Category="AssetDefaultName")
	FString AssetDefaultName;

	UPROPERTY(EditAnywhere, Category="GameplayClass")
	TSubclassOf<UObject> ParentGameplayClass;

	FGameplayCreationData():AssetDefaultName(TEXT("DefaultAssetName")){}
};


/**
 * 
 */
UCLASS(Config=Game,defaultconfig, NotPlaceable)
class UNREALGAMEPLAYTOOLKITEDITOR_API UGameplayCreationMenu : public UObject
{
    GENERATED_BODY()
public:

    UGameplayCreationMenu();

    UPROPERTY(Config, EditAnywhere, Category="Test")
    float testConfig;

	UPROPERTY(Config, EditAnywhere, Category="GameplayCreationMenu")
    TArray<FGameplayCreationData> Definitions;

    void AddMenuExtensions() const;
};
