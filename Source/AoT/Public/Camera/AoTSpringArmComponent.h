// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "AoTSpringArmComponent.generated.h"

/**
 * 
 */
UCLASS()
class AOT_API UAoTSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	void AdjustArmLengthForOwnerSpeed(float DeltaTime);
	
	UPROPERTY(EditDefaultsOnly)
	float MinTargetArmLength = 350.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxTargetArmLength = 425.f;

	UPROPERTY(EditDefaultsOnly)
	float ArmInterpSpeed = 3.f;

};
