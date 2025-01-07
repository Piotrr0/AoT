// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AoTProjectileAbility.h"
#include "GameplayTagContainer.h"
#include "HookAbility.generated.h"

/**
 * 
 */
UCLASS()
class AOT_API UHookAbility : public UAoTProjectileAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	bool bLeftHookFired;
	UPROPERTY(BlueprintReadWrite)
	bool bRightHookFired;

protected:

	virtual AAoTProjectile* SpawnProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation) override;
	virtual void SetProjectileProperties(AAoTProjectile* Projectile) override;

	UFUNCTION(BlueprintCallable)
	void CalculateHookSpawnAndEndLocation(const FGameplayTag& GearTag);


private:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayTag LeftGearTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayTag RightGearTag;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector HookSpawnLocation;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector HookEndLocation;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FGameplayTag HookGearTag;

	UPROPERTY(EditDefaultsOnly)
	float HookDistance = 10000.f;
};
