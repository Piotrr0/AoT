// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HookAbility.h"
#include "Interfaces/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor/HookProjectile.h"
#include "AoTGameplayTags.h"

void UHookAbility::BindCallbacksToDependencies()
{
	if (LeftHook && !LeftHook->HookLocationReceivedDelegate.IsBound())
	{
		LeftHook->HookLocationReceivedDelegate.AddUObject(this, &UHookAbility::HandleReceivedHookLocation);
	}
	if (RightHook && !RightHook->HookLocationReceivedDelegate.IsBound())
	{
		RightHook->HookLocationReceivedDelegate.AddUObject(this, &UHookAbility::HandleReceivedHookLocation);
	}
	if (LeftHook && !LeftHook->HookRetunedToOwnerDelegate.IsBound())
	{
		LeftHook->HookRetunedToOwnerDelegate.AddDynamic(this, &UHookAbility::HandleHookReturn);
	}
	if (RightHook && !RightHook->HookRetunedToOwnerDelegate.IsBound())
	{
		RightHook->HookRetunedToOwnerDelegate.AddDynamic(this, &UHookAbility::HandleHookReturn);
	}
}

void UHookAbility::SpawnHookProjectile(const FVector& SpawnLocation, const FRotator& SpawnRotation, const FGameplayTag& GearTag)
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(SpawnRotation.Quaternion());

	AActor* Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), HookClass, SpawnTransform);
	if (AHookProjectile* HookProjectile = Cast<AHookProjectile>(Projectile))
	{
		HookProjectile->FireSocket = GearTag;

		if (GearTag.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_LeftGear))
		{
			LeftHook = HookProjectile;
		}
		else
		{
			RightHook = HookProjectile;
		}
	}
	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
	BindCallbacksToDependencies();
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

void UHookAbility::HandleReceivedHookLocation(bool bForLeft, const FHitResult& HitResult)
{
	if (bForLeft)
	{
		bLeftHookHit = true;
	}
	else
	{
		bRightHookHit = true;
	}
}

void UHookAbility::HandleHookReturn(bool bForLeft)
{
	if (bForLeft)
	{
		LeftHook = nullptr;
	}
	else
	{
		RightHook = nullptr;
	}
}
