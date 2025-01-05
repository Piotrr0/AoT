// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/AoTInputConfig.h"

UInputAction* UAoTInputConfig::FindInputActionForTag(const FGameplayTag& InInputTag)
{
	for (const auto& AbilityInputAction : AbilityInputActions)
	{
		if (AbilityInputAction.InputTag == InInputTag)
			return AbilityInputAction.InputAction;
	}
	return nullptr;
}
