// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AoTProjectileAbility.h"
#include "GameplayTagContainer.h"
#include "HookAbility.generated.h"

class AHookProjectile;
struct FHookHitParams;

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
	
	UPROPERTY(BlueprintReadWrite)
	bool bLeftHookHit;

	UPROPERTY(BlueprintReadWrite)
	bool bRightHookHit;

	void BindCallbacksToDependencies();

	FVector GetHookPositionFromAnchors() const;

protected:

	UFUNCTION(BlueprintCallable)
	void SpawnHookProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation, const FGameplayTag& GearTag);

	UFUNCTION(BlueprintCallable)
	void ReleaseHook(const FGameplayTag& GearTag);

	UFUNCTION(BlueprintCallable)
	FHookSpawnParams CalculateHookSpawnParams(const FGameplayTag& GearTag) const;

	UFUNCTION()
	void HandleReceivedHookLocation(const FGameplayTag& GearTag, const FHookHitParams& HitParams);
	UFUNCTION()
	void HandleHookReturn(const FGameplayTag& GearTag);
		
	UPROPERTY(EditAnywhere)
	TSubclassOf<AHookProjectile> HookClass;

	TArray<FHookHitParams> LeftHookHitParams;
	TArray<FHookHitParams> RightHookHitParams;

private:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayTag LeftGearTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayTag RightGearTag;
};
