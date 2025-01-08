// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/AoTProjectile.h"
#include "GameplayTagContainer.h"
#include "HookProjectile.generated.h"

class UHookAbility;

DECLARE_MULTICAST_DELEGATE_TwoParams(FHookLocationReceived, const FGameplayTag&, const FHitResult&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHookRetunedToOwner, const FGameplayTag&, FireSocket);
/**
 * 
 */
UCLASS()
class AOT_API AHookProjectile : public AAoTProjectile
{
	GENERATED_BODY()

public:
	AHookProjectile();

	/* Tag for socket From which it was fired */
	UPROPERTY(BlueprintReadOnly)
	FGameplayTag FireSocket;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ReturnToOwner();

	UFUNCTION(BlueprintCallable)
	void PrematureReturn();

	FHookLocationReceived HookLocationReceivedDelegate;

	UPROPERTY(BlueprintCallable)
	FHookRetunedToOwner HookRetunedToOwnerDelegate;

protected:

	virtual void BeginPlay() override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HookLifeTime = 2.f;

	UPROPERTY(BlueprintReadWrite) /* Set to false in ReturnToOwner event blueprint */
	bool bLocationFound; /* Not set to false on hook realse */

	UPROPERTY(BlueprintReadWrite)
	bool bReturning;
};
