// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AoTPlayerState.h"
#include "AbilitySystemComponent.h"

AAoTPlayerState::AAoTPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));
}

UAbilitySystemComponent* AAoTPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
