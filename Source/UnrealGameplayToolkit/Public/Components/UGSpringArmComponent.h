// Copyright saberuster. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "UGSpringArmComponent.generated.h"

/**
 * add Zoom function
 */
UCLASS(ClassGroup=(UG),meta=(BlueprintSpawnableComponent))
class UNREALGAMEPLAYTOOLKIT_API UUGSpringArmComponent : public USpringArmComponent
{
    GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Zoom)
    uint32 bEnableZoom:1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Zoom)
    float ZoomMinLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Zoom)
    float ZoomMaxLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Zoom)
    float ZoomScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Zoom)
    float ZoomSpeed;

private:

    UPROPERTY(Transient)
    float DesiredArmLength;
    
public:

    virtual void BeginPlay() override;
    explicit UUGSpringArmComponent(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, Category=Zoom)
    void Zoom(float Offset);

    UFUNCTION(BlueprintCallable, Category=Zoom)
    void StopZoom();

    UFUNCTION(BlueprintPure, Category=Zoom)
    bool IsZoomEnable() const;
    
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    virtual void UpdateZoomLength(float DeltaTime);
};
