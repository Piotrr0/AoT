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

	/*PlayerInterface*/
	virtual bool GetLeftHookHit_Implementation() override;
	virtual bool GetRightHookHit_Implementation() override;
	virtual bool GetHookHit_Implementation() override;
	virtual bool GetIsBoosting_Implementation() override;
	virtual FVector GetHookPositionFromAnchors_Implementation() override;
	virtual UCableComponent* GetLeftCable_Implementation() override;
	virtual UCableComponent* GetRightCable_Implementation() override;

protected:

	void InitAbilityActorInfo() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UCableComponent> LeftCable;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UCableComponent> RightCable;

private:


};
