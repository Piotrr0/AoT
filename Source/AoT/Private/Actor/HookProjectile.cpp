// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/HookProjectile.h"
#include "AoTGameplayTags.h"
#include "AbilitySystem/Abilities/HookAbility.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/PlayerInterface.h"
#include "CableComponent.h"

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
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (PlayerPawn->Implements<UPlayerInterface>())
	{
		if (FireSocket.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_LeftGear))
		{
			UCableComponent* LeftCable = IPlayerInterface::Execute_GetLeftCable(PlayerPawn);
			LeftCable->SetVisibility(true);
			LeftCable->SetAttachEndTo(this, FName(""));
		}
		else if (FireSocket.MatchesTagExact(FAoTGameplayTags::Get().CombatSocket_RightGear))
		{
			UCableComponent* RightCable = IPlayerInterface::Execute_GetRightCable(PlayerPawn);
			RightCable->SetVisibility(true);
			RightCable->SetAttachEndTo(this, FName(""));
		}
	}
}

void AHookProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor)
	{
		bLocationFound = true;
		HookLocationReceivedDelegate.Broadcast(FireSocket, SweepResult);
	}
}
