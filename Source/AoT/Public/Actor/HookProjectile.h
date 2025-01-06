// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/AoTProjectile.h"
#include "GameplayTagContainer.h"
#include "HookProjectile.generated.h"

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
	FGameplayTag GearTag;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void HookReleased();

protected:

	virtual void BeginPlay() override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
};
