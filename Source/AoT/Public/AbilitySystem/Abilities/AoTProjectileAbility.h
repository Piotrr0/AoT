// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AoTGameplayAbility.h"
#include "AoTProjectileAbility.generated.h"

class AAoTProjectile;

/**
 * 
 */
UCLASS()
class AOT_API UAoTProjectileAbility : public UAoTGameplayAbility
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable)
	virtual AAoTProjectile* SpawnProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation);

	virtual void SetProjectileProperties(AAoTProjectile* Projectile);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAoTProjectile> ProjectileClass;

};
