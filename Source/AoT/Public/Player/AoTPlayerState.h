// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AoTPlayerState.generated.h"

class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class AOT_API AAoTPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAoTPlayerState();
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:


private:

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
};
