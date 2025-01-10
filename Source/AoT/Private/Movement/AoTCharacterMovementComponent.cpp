// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/AoTCharacterMovementComponent.h"
#include "Interfaces/PlayerInterface.h"

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
        }

        if (IsMovingOnGround() && !bIsBoosting && bHookHit)
        {
            const FVector SwingForce = CalculateSwingForce();
        }
    }
}

FVector UAoTCharacterMovementComponent::CalculateBoostForce()
{
    return FVector::ZeroVector;
}

FVector UAoTCharacterMovementComponent::CalculateSwingForce()
{
    return FVector::ZeroVector;
}
