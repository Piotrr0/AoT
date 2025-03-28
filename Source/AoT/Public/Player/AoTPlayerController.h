// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "AoTPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UAoTInputConfig;
class UAoTAbilitySystemComponent;
class UHookAbility;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class AOT_API AAoTPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LeftMouseButtonPressed();
	void RightMouseButtonPressed();
	void LeftMouseButtonReleased();
	void RightMouseButtonReleased();

	void JumpOrBoostButtonPressed();
	void JumpOrBoostButtonReleased();

	bool bBoosting;

private:

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UAoTAbilitySystemComponent* GetASC();

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AoTContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LeftAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> RightAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpOrBoostAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAoTInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAoTAbilitySystemComponent> AoTAbilitySystemComponent;

};
