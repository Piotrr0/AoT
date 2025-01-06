// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HookAbility.h"
#include "Interfaces/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UHookAbility::CalculateHookSpawnAndEndLocation(const FGameplayTag& GearTag)
{
	if (GetAvatarActorFromActorInfo()->Implements<UCombatInterface>())
	{
		HookSpawnLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), GearTag);

		const FRotator AimRotation = UGameplayStatics::GetPlayerPawn(this, 0)->GetBaseAimRotation();
		const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(AimRotation);

		HookEndLocation = HookSpawnLocation + (ForwardVector * HookDistance);
	}
}
