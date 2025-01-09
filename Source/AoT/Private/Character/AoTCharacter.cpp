// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AoTCharacter.h"
#include "Player/AoTPlayerState.h"
#include "AoTGameplayTags.h"
#include "AbilitySystem/AoTAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/HookAbility.h"
#include "AbilitySystem/Abilities/BoostAbility.h"

AAoTCharacter::AAoTCharacter()
{

}

void AAoTCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

bool AAoTCharacter::GetLeftHookHit_Implementation()
{
	if (UAoTAbilitySystemComponent* AoTASC = Cast<UAoTAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (const UHookAbility* HookAbility = Cast<UHookAbility>(AoTASC->GetAbilityInstanceByTag(FAoTGameplayTags::Get().Abilities_Hook)))
		{
			return HookAbility->bLeftHookHit;
		}
	}
	return false;
}

bool AAoTCharacter::GetRightHookHit_Implementation()
{
	if (UAoTAbilitySystemComponent* AoTASC = Cast<UAoTAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (const UHookAbility* HookAbility = Cast<UHookAbility>(AoTASC->GetAbilityInstanceByTag(FAoTGameplayTags::Get().Abilities_Hook)))
		{
			return HookAbility->bRightHookHit;
		}
	}
	return false;
}

bool AAoTCharacter::GetHookHit_Implementation()
{
	if (UAoTAbilitySystemComponent* AoTASC = Cast<UAoTAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (const UHookAbility* HookAbility = Cast<UHookAbility>(AoTASC->GetAbilityInstanceByTag(FAoTGameplayTags::Get().Abilities_Hook)))
		{
			return HookAbility->bRightHookHit || HookAbility->bLeftHookHit;
		}
	}
	return false;
}

bool AAoTCharacter::GetIsBoosting_Implementation()
{
	if (UAoTAbilitySystemComponent* AoTASC = Cast<UAoTAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (const UBoostAbility* BoostAbility = Cast<UBoostAbility>(AoTASC->GetAbilityInstanceByTag(FAoTGameplayTags::Get().Abilities_Boost)))
		{
			return BoostAbility->bIsBoosting;
		}
	}
	return false;
}

FVector AAoTCharacter::GetHookPositionFromAnchors_Implementation()
{
	if (UAoTAbilitySystemComponent* AoTASC = Cast<UAoTAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (const UHookAbility* HookAbility = Cast<UHookAbility>(AoTASC->GetAbilityInstanceByTag(FAoTGameplayTags::Get().Abilities_Hook)))
		{
			return HookAbility->GetHookPositionFromAnchors();
		}
	}
	return FVector::ZeroVector;
}

void AAoTCharacter::InitAbilityActorInfo()
{
	AAoTPlayerState* AoTPlayerState = Cast<AAoTPlayerState>(GetPlayerState());
	AoTPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AoTPlayerState, this);

	AbilitySystemComponent = AoTPlayerState->GetAbilitySystemComponent();
	AttributeSet = AoTPlayerState->GetAttributeSet();
	InitDefaultAttributes();
	InitDefaultAbilities();
}
