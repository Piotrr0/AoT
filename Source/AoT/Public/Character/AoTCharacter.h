// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AoTCharacterBase.h"
#include "Player/AoTPlayerController.h"
#include "AoTCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AOT_API AAoTCharacter : public AAoTCharacterBase
{
	GENERATED_BODY()
public:
	AAoTCharacter();
	virtual void PossessedBy(AController* NewController) override;

protected:

	void InitAbilityActorInfo() override;

private:


};
