// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AoTPlayerState.h"
#include "AbilitySystem/AoTAbilitySystemComponent.h"
#include "AbilitySystem/AoTAttributeSet.h"

AAoTPlayerState::AAoTPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAoTAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UAoTAttributeSet>(FName("AttributeSet"));
}

UAbilitySystemComponent* AAoTPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAoTPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
