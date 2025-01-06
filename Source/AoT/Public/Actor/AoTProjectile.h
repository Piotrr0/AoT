// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AoTProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UENUM(BlueprintType)
enum class EOverlapPolicy
{
	Destroy,
	Attach,
	Penetrate
};

UCLASS()
class AOT_API AAoTProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AAoTProjectile();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> CollisionSphere;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	EOverlapPolicy OverlapPolicy;
};
	