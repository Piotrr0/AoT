// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HookAbility.h"
#include "Interfaces/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor/HookProjectile.h"
#include "AoTGameplayTags.h"
#include "Interfaces/PlayerInterface.h"

FVector UHookAbility::GetHookPositionFromAnchors() const
{
	if (bRightHookHit && bLeftHookHit)
	{
		return UKismetMathLibrary::VLerp(LeftHookHitParams.Last().Impact, RightHookHitParams.Last().Impact, 0.5f);
	}
	if (bLeftHookHit)
	{
		return LeftHookHitParams.Last().Impact;
	}
	if (bRightHookHit)
	{
		return RightHookHitParams.Last().Impact;
	}
	return FVector::ZeroVector;
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
			LeftHook->HookLocationReceivedDelegate.AddUObject(this, &UHookAbility::HandleReceivedHookLocation);
			LeftHook->HookFreeLocationDelegate.AddUObject(this, &UHookAbility::HandleFreedLastHookLocation);
			LeftHook->HookRetunedToOwnerDelegate.AddDynamic(this, &UHookAbility::HandleHookReturn);
		}
		else
		{
			RightHook = HookProjectile;
			RightHook->HookLocationReceivedDelegate.AddUObject(this, &UHookAbility::HandleReceivedHookLocation);
			RightHook->HookFreeLocationDelegate.AddUObject(this, &UHookAbility::HandleFreedLastHookLocation);
			RightHook->HookRetunedToOwnerDelegate.AddDynamic(this, &UHookAbility::HandleHookReturn);
		}
	}
	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}

void UHookAbility::ReleaseHook(const FGameplayTag& GearTag)
{
	if (GearTag.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_LeftGear))
	{
		LeftHook->ReturnToOwner();
		bLeftHookHit = false;
		LeftHookHitParams.Empty();
	}
	else
	{
		RightHook->ReturnToOwner();
		bRightHookHit = false;
		RightHookHitParams.Empty();
	}

	if (!CheckNoLongerHooked())
	{
		IPlayerInterface::Execute_SetOrientRotationToMovement(GetAvatarActorFromActorInfo(), false);
	}
}

FHookSpawnParams UHookAbility::CalculateHookSpawnParams(const FGameplayTag& GearTag) const
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

void UHookAbility::HandleReceivedHookLocation(const FGameplayTag& GearTag, const FHookHitParams& HitParams)
{
	if (GearTag.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_LeftGear))
	{
		bLeftHookHit = true;
		LeftHookHitParams.Add(HitParams);
	}
	else
	{
		bRightHookHit = true;
		RightHookHitParams.Add(HitParams);
	}
	IPlayerInterface::Execute_SetOrientRotationToMovement(GetAvatarActorFromActorInfo(), false);
}

void UHookAbility::HandleHookReturn(const FGameplayTag& GearTag)
{
	if (GearTag.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_LeftGear))
	{
		LeftHook = nullptr;
	}
	else
	{
		RightHook = nullptr;
	}
}

void UHookAbility::HandleFreedLastHookLocation(const FGameplayTag& GearTag)
{
	if (GearTag.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_LeftGear))
	{
		LeftHookHitParams.Pop();
	}
	else
	{
		RightHookHitParams.Pop();
	}
}

bool UHookAbility::CheckNoLongerHooked()
{
	if (!bRightHookHit && !bLeftHookHit)
	{
		IPlayerInterface::Execute_UpdateCharacterRotation(GetAvatarActorFromActorInfo());
		IPlayerInterface::Execute_SetOrientRotationToMovement(GetAvatarActorFromActorInfo(), true);
		return true;
	}
	return false;
}