// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/HookProjectile.h"
#include "AoTGameplayTags.h"
#include "AbilitySystem/Abilities/HookAbility.h"

AHookProjectile::AHookProjectile()
{

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
	if (FireSocket.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_LeftGear))
	{
		bIsLeftSocket = true;
	}
	else
	{
		bIsLeftSocket = false;
	}
}

void AHookProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor)
	{
		bLocationFound = true;
		HookLocationReceivedDelegate.Broadcast(bIsLeftSocket, SweepResult);
	}
}
