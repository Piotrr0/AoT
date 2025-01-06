// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "AoTGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AOT_API UAoTGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> InputTags;

};
