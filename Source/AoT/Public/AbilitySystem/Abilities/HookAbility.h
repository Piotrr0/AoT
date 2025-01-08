// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AoTProjectileAbility.h"
#include "GameplayTagContainer.h"
#include "HookAbility.generated.h"

class AHookProjectile;

USTRUCT(BlueprintType)
struct FHookSpawnParams
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	FVector SpawnLocation = FVector();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FRotator SpawnRotation = FRotator();
};

/**
 * 
 */
UCLASS()
class AOT_API UHookAbility : public UAoTProjectileAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AHookProjectile> LeftHook;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AHookProjectile> RightHook;

protected:

	UFUNCTION(BlueprintCallable)
	AHookProjectile* SpawnHookProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation, const FGameplayTag& GearTag);

	UFUNCTION(BlueprintCallable)
	FHookSpawnParams CalculateHookSpawnParams(const FGameplayTag& GearTag);

private:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayTag LeftGearTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayTag RightGearTag;

	UPROPERTY(EditDefaultsOnly)
	float HookDistance = 10000.f;
};
