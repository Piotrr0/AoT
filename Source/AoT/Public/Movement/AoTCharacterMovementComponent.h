// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AoTCharacterMovementComponent.generated.h"

class IPlayerInterface;

/**
 * 
 */
UCLASS()
class AOT_API UAoTCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UAoTCharacterMovementComponent();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float BoostForceMultiplier = 1.f;
	float SwingForceMultiplier = 1.f;
	
protected:

	void AddAirForces();
private:

	FVector CalculateBoostForce() const;
	FVector CalculateSwingForce() const;

};
