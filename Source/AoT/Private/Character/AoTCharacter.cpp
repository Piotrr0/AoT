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
	CalculateVelocityDotHook();
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

FRotator AAoTCharacter::UpdateCharacterRotationWhileHooked()
{
	const FRotator HookLookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), IPlayerInterface::Execute_GetHookPositionFromAnchors(this));

	const float EffectiveSidewaysAngle = IPlayerInterface::Execute_GetIsBoosting(this) ? MaxCharacterAngleBoosting : MaxCharacterAngle;
	const float MappedSidewaysAngle = UKismetMathLibrary::MapRangeClamped(VelocityDotHook, -1.f, 1.f, -EffectiveSidewaysAngle, EffectiveSidewaysAngle);

	const FRotator SidewaysRotation = UKismetMathLibrary::RotatorFromAxisAndAngle(GetActorForwardVector(), MappedSidewaysAngle);

	FRotator RotationOffset = FRotator::ZeroRotator;
	if (!GetCharacterMovement()->IsMovingOnGround())
	{
		RotationOffset = SidewaysRotation;
	}

	const FRotator BlendedRotation = UKismetMathLibrary::RLerp(UKismetMathLibrary::MakeRotFromX(GetVelocity()), HookLookAtRotation, 0.5f, true);
	const FRotator YawOnlyRotation = FRotator(0.f, BlendedRotation.Yaw, 0.f);

	const FRotator CombinedRotation = UKismetMathLibrary::ComposeRotators(YawOnlyRotation, RotationOffset);
	const FRotator InterpolatedRotation = UKismetMathLibrary::RInterpTo(GetActorRotation(), CombinedRotation, GetWorld()->GetDeltaSeconds(), 4.f);

	if (IPlayerInterface::Execute_GetHookHit(this))
	{
		HookedDesiredRotation = InterpolatedRotation;
		SetActorRotation(HookedDesiredRotation);

		return HookLookAtRotation;
	}

	return HookLookAtRotation;
}

void AAoTCharacter::CalculateVelocityDotHook()
{
	const FVector VelocityXY = FVector(GetVelocity().X, GetVelocity().Y, 0.f).GetSafeNormal(0.00001f);
	const FRotator CurrentHookRotation = CachedHookRotation;
	VelocityDotHook = UKismetMathLibrary::Dot_VectorVector(VelocityXY, UKismetMathLibrary::GetRightVector(CurrentHookRotation));

	CachedHookRotation = UpdateCharacterRotationWhileHooked();
}
