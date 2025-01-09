// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AoTGameplayAbility.h"
#include "BoostAbility.generated.h"

/**
 * 
 */
UCLASS()
class AOT_API UBoostAbility : public UAoTGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BoostForce = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StartBoostForce = 1000.f;

protected:

	UFUNCTION(BlueprintCallable)
	void ApplyBoost();


};
