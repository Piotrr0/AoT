// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/BoostAbility.h"
#include "Interfaces/PlayerInterface.h"
#include "Interfaces/CombatInterface.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBoostAbility::ApplyBoost()
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (AvatarActor->Implements<UPlayerInterface>() && AvatarActor->Implements<UCombatInterface>())
	{
		const FVector Direction = (IPlayerInterface::Execute_GetHookPositionFromAnchors(AvatarActor) - AvatarActor->GetActorLocation()).GetSafeNormal();
		ICombatInterface::Execute_GetMovement(AvatarActor)->AddImpulse(Direction * StartBoostForce);
	}
}
