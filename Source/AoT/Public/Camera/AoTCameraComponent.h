// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "AoTCameraComponent.generated.h"

/**
 * 
 */
UCLASS()
class AOT_API UAoTCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void AdjustFOVForOwnerSpeed(float DeltaTime);

	UPROPERTY(EditDefaultsOnly)
	float MinFOV = 90;

	UPROPERTY(EditDefaultsOnly)
	float MaxFOV = 110.f;

	UPROPERTY(EditDefaultsOnly)
	float FOVInterpSpeed = 3.f;

};
