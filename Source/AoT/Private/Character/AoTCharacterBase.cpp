// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AoTCharacterBase.h"
#include "AbilitySystemComponent.h"

AAoTCharacterBase::AAoTCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

UAbilitySystemComponent* AAoTCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAoTCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAoTCharacterBase::InitAbilityActorInfo()
{

}
