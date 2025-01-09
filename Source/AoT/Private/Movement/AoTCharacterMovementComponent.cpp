// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/AoTCharacterMovementComponent.h"

void UAoTCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CalculateAirForces();
}

void UAoTCharacterMovementComponent::CalculateAirForces()
{

}

