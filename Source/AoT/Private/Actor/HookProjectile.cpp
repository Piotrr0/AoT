// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/HookProjectile.h"
#include "AoTGameplayTags.h"
#include "AbilitySystem/Abilities/HookAbility.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/PlayerInterface.h"
#include "Interfaces/CombatInterface.h"
#include "CableComponent.h"
#include "Kismet/KismetMathLibrary.h"

AHookProjectile::AHookProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHookProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DetectRopeCollision();
	NoLongerRopeBlock();
}

void AHookProjectile::PrematureReturn()
{
	if (!bLocationFound)
	{
		ReturnToOwner();
	}
}

void AHookProjectile::BeginPlay()
{
	Super::BeginPlay();
	if (GetPlayerPawn()->Implements<UPlayerInterface>())
	{
		if (FireSocket.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_LeftGear))
		{
			UCableComponent* LeftCable = IPlayerInterface::Execute_GetLeftCable(GetPlayerPawn());
			LeftCable->SetVisibility(true);
			LeftCable->SetAttachEndTo(this, FName(""));
		}
		else if (FireSocket.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_RightGear))
		{
			UCableComponent* RightCable = IPlayerInterface::Execute_GetRightCable(GetPlayerPawn());
			RightCable->SetVisibility(true);
			RightCable->SetAttachEndTo(this, FName(""));
		}
	}
}

void AHookProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (!bLocationFound && OtherActor && !OtherActor->Implements<UPlayerInterface>())
	{
		bLocationFound = true;

		FHookHitParams HitParams;
		HitParams.Impact = SweepResult.ImpactPoint;
		HitParams.Normal = SweepResult.ImpactNormal;
		HitParams.Tangent = FVector::ZeroVector;

		HitData.Add(HitParams);
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
			HookFreeLocationDelegate.Broadcast(FireSocket);
		}
	}
}