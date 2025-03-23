// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/AoTCameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UAoTCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AdjustFOVForOwnerSpeed(DeltaTime);
}

void UAoTCameraComponent::AdjustFOVForOwnerSpeed(float DeltaTime)
{
	if (const ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		const float OwnerMaxSpeed = Owner->GetCharacterMovement()->MaxWalkSpeed;
		const float OwnerVelocity = Owner->GetVelocity().Size();
		const float DesiredFOV = UKismetMathLibrary::MapRangeClamped(OwnerVelocity, OwnerMaxSpeed, OwnerMaxSpeed + 200.f, MinFOV, MaxFOV);

		SetFieldOfView(UKismetMathLibrary::FInterpTo(FieldOfView, DesiredFOV, DeltaTime, FOVInterpSpeed));
	}
}
