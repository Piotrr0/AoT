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
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class AOT_API AAoTPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	FVector2D GetHookStatus() const { return HookStatus; }


protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	/*
	* Explanation of the Values:
	* {1, 0}: Left hook fired.
	* {0, 1}: Right hook fired.
	* {0, 0}: No hooks fired.
	* {1, 1}: Both hooks fired.
	*/
	void GetHookFireStatus(const FInputActionValue& Value);


private:

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UAoTAbilitySystemComponent* GetASC();
	FVector2D HookStatus;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AoTContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> HookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UAoTInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAoTAbilitySystemComponent> AoTAbilitySystemComponent;

};
