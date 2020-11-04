// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "UGDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=UG, meta=(DisplayName="UnrealGameplayToolkit"))
class UNREALGAMEPLAYTOOLKIT_API UUGDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UUGDeveloperSettings();
	
	virtual FName GetCategoryName() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AStarSearchAlgorithm")
	uint32 bEnableRelax: 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AStarSearchAlgorithm", meta=(MetaClass="AStarSearchHeuristicCalculation"))
	FSoftClassPath DefaultHeuristicCalculationClass;
};
