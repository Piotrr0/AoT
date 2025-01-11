// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/AoTCharacterMovementComponent.h"
#include "Interfaces/PlayerInterface.h"
#include "Kismet/KismetMathLibrary.h"

void UAoTCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AddAirForces();
}

UAoTCharacterMovementComponent::UAoTCharacterMovementComponent()
{
}

void UAoTCharacterMovementComponent::AddAirForces()
{
    AActor* Owner = GetOwner();
    if (Owner && Owner->Implements<UPlayerInterface>())
    {
        const bool bIsBoosting = IPlayerInterface::Execute_GetIsBoosting(Owner);
        const bool bHookHit = IPlayerInterface::Execute_GetHookHit(Owner);

        if (bIsBoosting && bHookHit)
        {
            const FVector BoostForce = CalculateBoostForce();
            AddForce(BoostForce * BoostForceMultiplier);
        }

        if (IsMovingOnGround() && !bIsBoosting && bHookHit)
        {
            const FVector SwingForce = CalculateSwingForce();
        }
    }
}

FVector UAoTCharacterMovementComponent::CalculateBoostForce() const
{
    const FVector OwnerLocation = GetOwner()->GetActorLocation();
    const FVector HookPosition = IPlayerInterface::Execute_GetHookPositionFromAnchors(GetOwner());

    const FVector Direction = (HookPosition - OwnerLocation).GetSafeNormal();
    const float Distance = FVector::Dist(OwnerLocation, HookPosition);
    const float BoostScale = UKismetMathLibrary::MapRangeClamped(Distance, 0.f, 4000.f, 200000.f, 400000.f);

    return (Direction * BoostScale) + FVector(0.f, 0.f, 60000.f);
}

FVector UAoTCharacterMovementComponent::CalculateSwingForce() const
{
    const FVector OwnerLocation = GetOwner()->GetActorLocation();
    const FVector HookPosition = IPlayerInterface::Execute_GetHookPositionFromAnchors(GetOwner());

    const FVector Direction = (HookPosition - OwnerLocation).GetSafeNormal();
    const FVector HookApproachVelocity = UKismetMathLibrary::Vector_ClampSize2D(Velocity, 400.f, 1200.f);
    const float HookMotionAlignment = FVector::DotProduct(HookApproachVelocity, Direction);

    FVector SwingForce = (Direction * HookMotionAlignment) * -2.f;

    const float ZOffset = HookPosition.Z - OwnerLocation.Z;
    const float HeightAdjustmentScale = UKismetMathLibrary::MapRangeClamped(ZOffset, -1000.f, 0.f, 0.75f, 1.f);
    SwingForce *= HeightAdjustmentScale;

    const float SwingForceAlignmentFactor = FVector::DotProduct(-Direction, SwingForce.GetSafeNormal());
    if (UKismetMathLibrary::NearlyEqual_FloatFloat(SwingForceAlignmentFactor, 1.f, 0.1f))
    {
        return SwingForce;
    }

    return FVector::ZeroVector;
}
