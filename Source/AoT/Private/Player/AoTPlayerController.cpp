// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AoTPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Input/AoTInputComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AoTAbilitySystemComponent.h"
#include "AbilitySystem/AoTGameplayAbility.h"


void AAoTPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AoTContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AoTContext, 0);
}

void AAoTPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAoTInputComponent* AoTInputComponent = CastChecked<UAoTInputComponent>(InputComponent);
	if (IsValid(AoTInputComponent))
	{
		AoTInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAoTPlayerController::Move);
		AoTInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAoTPlayerController::Look);
		AoTInputComponent->BindAction(HookAction, ETriggerEvent::Triggered, this, &AAoTPlayerController::GetHookFireStatus);

		AoTInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	}
}

void AAoTPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AAoTPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAoTPlayerController::GetHookFireStatus(const FInputActionValue& Value)
{
	FVector2D HookStatusValue = Value.Get<FVector2D>();
	HookStatus = HookStatusValue;
}

void AAoTPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (GetASC())
	{
		GetASC()->AbilityInputTagPressed(InputTag);
	}
}

void AAoTPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC())
	{
		GetASC()->AbilityInputTagReleased(InputTag);
	}
}

void AAoTPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC())
	{
		GetASC()->AbilityInputTagHeld(InputTag);
	}
}

UAoTAbilitySystemComponent* AAoTPlayerController::GetASC()
{
	if (AoTAbilitySystemComponent == nullptr)
	{
		AoTAbilitySystemComponent = Cast<UAoTAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return AoTAbilitySystemComponent;
}
