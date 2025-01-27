// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AoTCharacter.h"
#include "Player/AoTPlayerState.h"
#include "AoTGameplayTags.h"
#include "AbilitySystem/AoTAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/HookAbility.h"
#include "AbilitySystem/Abilities/BoostAbility.h"
#include "CableComponent.h"


AAoTCharacter::AAoTCharacter()
{
	LeftCable = CreateDefaultSubobject<UCableComponent>(FName("LeftCable"));
	RightCable = CreateDefaultSubobject<UCableComponent>(FName("RightCable"));
}

void AAoTCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
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
