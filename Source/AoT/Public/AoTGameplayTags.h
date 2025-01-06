// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

struct FAoTGameplayTags
{
public:
	static const FAoTGameplayTags& Get() { return GameplayTags; }
	static void InitNativeGameplayTags();

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;

	FGameplayTag CombatSocket_LeftGear;
	FGameplayTag CombatSocket_RightGear;

private:

	static FAoTGameplayTags GameplayTags;

};