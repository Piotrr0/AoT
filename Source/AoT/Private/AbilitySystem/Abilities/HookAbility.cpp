// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HookAbility.h"
#include "Interfaces/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor/HookProjectile.h"

AHookProjectile* UHookAbility::SpawnHookProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation, const FGameplayTag& GearTag)
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(SpawnRotation.Quaternion());

	AHookProjectile* Projectile = GetWorld()->SpawnActorDeferred<AHookProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	Projectile->OwningAbility = this;
	Projectile->FireSocket = GearTag;

	Projectile->FinishSpawning(SpawnTransform);
	return Projectile;
}

FHookSpawnParams UHookAbility::CalculateHookSpawnParams(const FGameplayTag& GearTag)
{
	FHookSpawnParams Params;

	if (GetAvatarActorFromActorInfo()->Implements<UCombatInterface>())
	{
		const FVector SpawnLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), GearTag);
		const FRotator AimRotation = UGameplayStatics::GetPlayerPawn(this, 0)->GetBaseAimRotation();
		const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(AimRotation);

		Params.SpawnLocation = SpawnLocation;
		Params.SpawnRotation = ForwardVector.Rotation();
	}
	return Params;
}
