// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AoTCharacter.h"
#include "Player/AoTPlayerState.h"
#include "AoTGameplayTags.h"
#include "AbilitySystem/AoTAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/HookAbility.h"
#include "AbilitySystem/Abilities/BoostAbility.h"
#include "CableComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "Movement/AoTCharacterMovementComponent.h"


AAoTCharacter::AAoTCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	LeftCable = CreateDefaultSubobject<UCableComponent>(FName("LeftCable"));
	RightCable = CreateDefaultSubobject<UCableComponent>(FName("RightCable"));
}

void AAoTCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

void AAoTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetCharacterRotationWhileHooked();
}

bool AAoTCharacter::GetLeftHookHit_Implementation()
{
	if (const UHookAbility* HookAbility = Cast<UHookAbility>(GetASC()->GetAbilityInstanceByTag(FAoTGameplayTags::Get().Abilities_Hook)))
	{
		return HookAbility->bLeftHookHit;
	}
	return false;
}

bool AAoTCharacter::GetRightHookHit_Implementation()
{
	if (const UHookAbility* HookAbility = Cast<UHookAbility>(GetASC()->GetAbilityInstanceByTag(FAoTGameplayTags::Get().Abilities_Hook)))
	{
		return HookAbility->bRightHookHit;
	}
	return false;
}

bool AAoTCharacter::GetHookHit_Implementation()
{
	if (const UHookAbility* HookAbility = Cast<UHookAbility>(GetASC()->GetAbilityInstanceByTag(FAoTGameplayTags::Get().Abilities_Hook)))
	{
		return HookAbility->bRightHookHit || HookAbility->bLeftHookHit;
	}
	return false;
}

bool AAoTCharacter::GetIsBoosting_Implementation()
{
	if (const UBoostAbility* BoostAbility = Cast<UBoostAbility>(GetASC()->GetAbilityInstanceByTag(FAoTGameplayTags::Get().Abilities_Boost)))
	{
		return BoostAbility->bIsBoosting;
	}
	return false;
}

FVector AAoTCharacter::GetHookPositionFromAnchors_Implementation()
{
	if (const UHookAbility* HookAbility = Cast<UHookAbility>(GetASC()->GetAbilityInstanceByTag(FAoTGameplayTags::Get().Abilities_Hook)))
	{
		return HookAbility->GetHookPositionFromAnchors();
	}
	return FVector::ZeroVector;
}

UCableComponent* AAoTCharacter::GetLeftCable_Implementation()
{
	return LeftCable;
}

UCableComponent* AAoTCharacter::GetRightCable_Implementation()
{
	return RightCable;
}

void AAoTCharacter::SetOrientRotationToMovement_Implementation(bool bOrientRotationToMovement)
{
	GetCharacterMovement()->bOrientRotationToMovement = bOrientRotationToMovement;
}

void AAoTCharacter::InitAbilityActorInfo()
{
	AAoTPlayerState* AoTPlayerState = Cast<AAoTPlayerState>(GetPlayerState());
	AoTPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AoTPlayerState, this);

	AbilitySystemComponent = AoTPlayerState->GetAbilitySystemComponent();
	AttributeSet = AoTPlayerState->GetAttributeSet();
	InitDefaultAttributes();
	InitDefaultAbilities();
	InitDefaultPassiveAbilities();
}

void AAoTCharacter::SetCharacterRotationWhileHooked()
{
	if (GetHookHit_Implementation())
	{
		const FVector VelocityDirection = FVector(GetVelocity().X, GetVelocity().Y, 0.f).GetSafeNormal();
		const FRotator TargetLookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetHookPositionFromAnchors_Implementation());

		const float LateralMovementFactor = UKismetMathLibrary::Dot_VectorVector(VelocityDirection, UKismetMathLibrary::GetRightVector(TargetLookRotation));
		const float MaxLateralAngle = GetIsBoosting_Implementation() ? MaxCharacterAngleBoosting : MaxCharacterAngle;
		const float MappedLateralAngle = UKismetMathLibrary::MapRangeClamped(LateralMovementFactor, -1.f, 1.f, -MaxLateralAngle, MaxLateralAngle);

		FRotator LateralTiltRotation = FRotator::ZeroRotator;
		if (!GetCharacterMovement()->IsMovingOnGround())
		{
			LateralTiltRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(GetActorForwardVector(), MappedLateralAngle);
		}

		const FRotator VelocityBasedRotation = UKismetMathLibrary::MakeRotFromX(GetVelocity());
		const FRotator BlendedLookRotation = UKismetMathLibrary::RLerp(VelocityBasedRotation, TargetLookRotation, 0.5f, true);
		const FRotator YawOnlyRotation = FRotator(0.f, BlendedLookRotation.Yaw, 0.f);

		const FRotator CombinedRotation = UKismetMathLibrary::ComposeRotators(YawOnlyRotation, LateralTiltRotation);
		const FRotator SmoothedRotation = UKismetMathLibrary::RInterpTo(GetActorRotation(), CombinedRotation, GetWorld()->GetDeltaSeconds(), 4.f);
		SetActorRotation(SmoothedRotation);
	}
}