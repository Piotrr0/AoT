// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

class UCableComponent;

/**
 * 
 */
class AOT_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetLeftHookHit();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetRightHookHit();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetHookHit();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsBoosting();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetHookPositionFromAnchors();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UCableComponent* GetLeftCable();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UCableComponent* GetRightCable();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateCharacterRotation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetOrientRotationToMovement(bool bOrientRotationToMovement);
};
