// Copyright saberuster. All Rights Reserved.


#include "Components/UGSpringArmComponent.h"

void UUGSpringArmComponent::BeginPlay()
{
    Super::BeginPlay();
    DesiredArmLength = TargetArmLength;
}

UUGSpringArmComponent::UUGSpringArmComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bEnableZoom = true;
    ZoomMinLength = 200.f;
    ZoomMaxLength = 500.f;
    ZoomScale = 1.f;
    ZoomSpeed = 100.f;
    DesiredArmLength = 0.f;
}

void UUGSpringArmComponent::Zoom(float Offset)
{
    if (!FMath::IsNearlyEqual(0.f, Offset))
    {
        DesiredArmLength = FMath::Clamp(DesiredArmLength + ZoomScale * Offset, ZoomMinLength, ZoomMaxLength);
    }
}

void UUGSpringArmComponent::StopZoom()
{
    DesiredArmLength = TargetArmLength;
}

bool UUGSpringArmComponent::IsZoomEnable() const
{
    return bEnableZoom;
}

void UUGSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
    UpdateZoomLength(DeltaTime);
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UUGSpringArmComponent::UpdateZoomLength(float DeltaTime)
{
    if (!FMath::IsNearlyEqual(DesiredArmLength, TargetArmLength))
    {
        TargetArmLength = FMath::FInterpTo(TargetArmLength, DesiredArmLength, DeltaTime, ZoomSpeed);
    }
}
