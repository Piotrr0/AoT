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

FVector UAoTCharacterMovementComponent::CalculateBoostForce()
{
    const FVector OwnerLocation = GetOwner()->GetActorLocation();
    const FVector HookPosition = IPlayerInterface::Execute_GetHookPositionFromAnchors(GetOwner());

    const FVector Direction = (HookPosition - GetOwner()->GetActorLocation()).GetSafeNormal();
    const float Distance = FVector::Dist(OwnerLocation, HookPosition);
    const float BoostMagnitude = UKismetMathLibrary::MapRangeClamped(Distance, 0.f, 4000.f, 200000.f, 400000.f);

    return (Direction * BoostMagnitude) + FVector(0.f, 0.f, 60000.f);
}

FVector UAoTCharacterMovementComponent::CalculateSwingForce()
{
    return FVector::ZeroVector;
}
