// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AoTCharacterBase.h"
#include "Interfaces/PlayerInterface.h"

#include "AoTCharacter.generated.h"

class UCableComponent;

/**
 * 
 */
UCLASS()
class AOT_API AAoTCharacter : public AAoTCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
public:
	AAoTCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaTime) override;

	/*PlayerInterface*/
	virtual bool GetLeftHookHit_Implementation() override;
	virtual bool GetRightHookHit_Implementation() override;
	virtual bool GetHookHit_Implementation() override;
	virtual bool GetIsBoosting_Implementation() override;
	virtual FVector GetHookPositionFromAnchors_Implementation() override;
	virtual UCableComponent* GetLeftCable_Implementation() override;
	virtual UCableComponent* GetRightCable_Implementation() override;
	virtual void SetOrientRotationToMovement_Implementation(bool bOrientRotationToMovement) override;

protected:

	void InitAbilityActorInfo() override;
	FRotator UpdateCharacterRotationWhileHooked();
	void CalculateVelocityDotHook();

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UCableComponent> LeftCable;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UCableComponent> RightCable;

private:

	FRotator HookedDesiredRotation;
	FRotator CachedHookRotation;
	float VelocityDotHook;

	UPROPERTY(EditDefaultsOnly)
	float MaxCharacterAngle = 30.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxCharacterAngleBoosting = 30.f;
};
