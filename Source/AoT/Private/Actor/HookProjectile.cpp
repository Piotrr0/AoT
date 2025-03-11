// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/HookProjectile.h"
#include "AoTGameplayTags.h"
#include "AbilitySystem/Abilities/HookAbility.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/PlayerInterface.h"
#include "Interfaces/CombatInterface.h"
#include "CableComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actor/Rope.h"

AHookProjectile::AHookProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHookProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DetectRopeCollision();
	NoLongerRopeBlock();
	UpdateRope();
}

void AHookProjectile::PrematureReturn()
{
	if (!bLocationFound)
	{
		ReturnToOwner();
	}
}

void AHookProjectile::DestroyRopeParts()
{
	for (ARope* Rope : RopeParts)
	{
		Rope->Destroy();
	}
	RopeParts.Empty();
}

void AHookProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (GetPlayerPawn()->Implements<UPlayerInterface>())
	{
		LeftPlayerCable = IPlayerInterface::Execute_GetLeftCable(GetPlayerPawn());
		RightPlayerCable = IPlayerInterface::Execute_GetRightCable(GetPlayerPawn());

		if (FireSocket.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_LeftGear))
		{
			SetRopeVisiblity(LeftPlayerCable, true);
			if (LeftPlayerCable)
			{
				LeftPlayerCable->SetAttachEndTo(this, FName(""));
			}
		}

		if (FireSocket.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_RightGear))
		{
			SetRopeVisiblity(RightPlayerCable, true);
			if (RightPlayerCable)
			{
				RightPlayerCable->SetAttachEndTo(this, FName(""));
			}
		}
	}
}

void AHookProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (!bLocationFound && OtherActor && !OtherActor->Implements<UPlayerInterface>())
	{
		bLocationFound = true;

		if (FireSocket.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_LeftGear))
		{
			SetRopeVisiblity(LeftPlayerCable, false);
		}

		if (FireSocket.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_RightGear))
		{
			SetRopeVisiblity(RightPlayerCable, false);
		}

		FHookHitParams HitParams;
		HitParams.Impact = SweepResult.ImpactPoint;
		HitParams.Normal = SweepResult.ImpactNormal;
		HitParams.Tangent = FVector::ZeroVector;

		HitData.Add(HitParams);
		HandleNewRopeBlock();
		HookLocationReceivedDelegate.Broadcast(FireSocket, HitParams);
	}
}

void AHookProjectile::DetectRopeCollision()
{
	if (!bReturning && !HitData.IsEmpty() && GetPlayerPawn()->Implements<UCombatInterface>())
	{
		const FVector LastHitLocation = HitData.Last().Impact;
		const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetPlayerPawn(), FireSocket);
		const FVector End = UKismetMathLibrary::VLerp(SocketLocation, LastHitLocation, 0.95);

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, SocketLocation, End, ECollisionChannel::ECC_Visibility);
		if (HitResult.bBlockingHit)
		{
			FHitResult ReverseHitResult;
			GetWorld()->LineTraceSingleByChannel(ReverseHitResult, LastHitLocation, SocketLocation, ECollisionChannel::ECC_Visibility);

			const FVector HookPointNormal = HitData.Last().Normal;
			const FVector HookPointOffset = UKismetMathLibrary::VLerp(HitResult.ImpactNormal, HookPointNormal, 0.5);

			FHookHitParams HookHitParams;
			HookHitParams.Impact = HitResult.ImpactPoint + HookPointOffset;
			HookHitParams.Normal = UKismetMathLibrary::VLerp(HitResult.Normal, ReverseHitResult.Normal, 0.5f).GetSafeNormal(0.0001f);
			HookHitParams.Tangent = FVector::CrossProduct(HitResult.ImpactNormal, ReverseHitResult.ImpactNormal);

			HitData.Add(HookHitParams);
			HandleNewRopeBlock();
			HookLocationReceivedDelegate.Broadcast(FireSocket, HookHitParams);
		}
	}
}

void AHookProjectile::NoLongerRopeBlock()
{
	if (!bReturning && HitData.Num() >= 2)
	{
		const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetPlayerPawn(), FireSocket);
		const FVector End = UKismetMathLibrary::VLerp(SocketLocation, HitData[HitData.Num() - 2].Impact, 0.99f);
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, SocketLocation, End, ECollisionChannel::ECC_Visibility);
		if (!HitResult.bBlockingHit)
		{
			HitData.Pop();
			HandleFreedRopeBlock();
			HookFreeLocationDelegate.Broadcast(FireSocket);
		}
	}
}

void AHookProjectile::HandleNewRopeBlock()
{
	const FTransform RopeSpawnTransform = FTransform();
	AActor* RopeActor = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), RopeClass, RopeSpawnTransform);
	ARope* Rope = Cast<ARope>(RopeActor);
	RopeParts.AddUnique(Rope);
	UGameplayStatics::FinishSpawningActor(RopeActor, RopeSpawnTransform);
}

void AHookProjectile::HandleFreedRopeBlock()
{
	if (RopeParts.IsEmpty()) return;

	RopeParts.Last()->Destroy();
	RopeParts.RemoveAt(RopeParts.Num() - 1);
}

void AHookProjectile::UpdateRope()
{
	if (bLocationFound)
	{
		const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetPlayerPawn(), FireSocket);

		TArray<FVector> HitLocations;
		for (const FHookHitParams& HitParam : HitData)
		{
			HitLocations.Add(HitParam.Impact);
		}
		HitLocations.Add(SocketLocation);

		for (int32 i = 0; i < HitLocations.Num() - 1; i++)
		{
			if (RopeParts[i])
			{
				RopeParts[i]->SetRopeTransform(HitLocations[i + 1], HitLocations[i]);
			}
		}
	}
}

void AHookProjectile::SetRopeVisiblity(UCableComponent* Cable, bool bVisible)
{
	if(Cable)
		Cable->SetVisibility(bVisible);
}
