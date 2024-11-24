// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "AoTPlayerState.generated.h"

class UAoTAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class AOT_API AAoTPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAoTPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintPure)
	UAoTAbilitySystemComponent* GetAoTAbilitySystemComponent() const;

private:
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UAoTAbilitySystemComponent> AbilitySystemComponent;
};
