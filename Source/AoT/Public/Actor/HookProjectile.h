// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/AoTProjectile.h"
#include "GameplayTagContainer.h"
#include "HookProjectile.generated.h"

class UHookAbility;

USTRUCT(BlueprintType)
struct FHookHitParams
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	FVector Impact;

	UPROPERTY(VisibleAnywhere)
	FVector Normal;

	UPROPERTY(VisibleAnywhere)
	FVector Tangent;
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FHookLocationReceived, const FGameplayTag&, const FHookHitParams&);
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
	virtual void Tick(float DeltaTime) override;

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
	void DetectRopeCollision();
	void NoLongerRopeBlock();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float HookLifeTime = 1.5f;

	UPROPERTY(BlueprintReadWrite) /* Set to false in ReturnToOwner event blueprint */
	bool bLocationFound = false; /* Not set to false on hook release */

	UPROPERTY(BlueprintReadWrite)
	bool bReturning = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere);
	TArray<FHookHitParams> HitData;
};
