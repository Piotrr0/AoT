// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/AoTSpringArmComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UAoTSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AdjustArmLengthForOwnerSpeed(DeltaTime);
}

void UAoTSpringArmComponent::AdjustArmLengthForOwnerSpeed(float DeltaTime)
{
	if (const ACharacter* Owner = Cast<ACharacter>(GetOwner()))
	{
		const float OwnerMaxSpeed = Owner->GetCharacterMovement()->MaxWalkSpeed;
		const float OwnerVelocity = Owner->GetVelocity().Size();
		const float DesiredArmLength = UKismetMathLibrary::MapRangeClamped(OwnerVelocity, OwnerMaxSpeed, OwnerMaxSpeed + 200.f, MinTargetArmLength, MaxTargetArmLength);

		TargetArmLength = UKismetMathLibrary::FInterpTo(TargetArmLength, DesiredArmLength, DeltaTime, ArmInterpSpeed);
	}
}
