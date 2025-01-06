// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AoTProjectileAbility.h"
#include "Actor/AoTProjectile.h"

AAoTProjectile* UAoTProjectileAbility::SpawnProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation)
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(SpawnRotation.Quaternion());
	AAoTProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAoTProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	SetProjectileProperties(Projectile);

	Projectile->FinishSpawning(SpawnTransform);
	return Projectile;
}

void UAoTProjectileAbility::SetProjectileProperties(AAoTProjectile* Projectile)
{

}

