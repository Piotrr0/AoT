// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PlayerState/AoTPlayerState.h"
#include "AbilitySystem/AoTAbilitySystemComponent.h"

AAoTPlayerState::AAoTPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAoTAbilitySystemComponent>(FName("AbilitySystemComponent"));
}

UAbilitySystemComponent* AAoTPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAoTAbilitySystemComponent* AAoTPlayerState::GetAoTAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
