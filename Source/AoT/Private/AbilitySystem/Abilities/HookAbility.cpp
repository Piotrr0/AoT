// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HookAbility.h"
#include "Interfaces/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor/HookProjectile.h"

AAoTProjectile* UHookAbility::SpawnProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation)
{
	return Super::SpawnProjectile(SpawnLocation, SpawnRotation);
}

void UHookAbility::SetProjectileProperties(AAoTProjectile* Projectile)
{
	Super::SetProjectileProperties(Projectile);
	if (AHookProjectile* HookProjectile = Cast<AHookProjectile>(Projectile))
	{
		if (HookGearTag.IsValid())
		{
			HookProjectile->GearTag = HookGearTag;
		}
	}
}

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
