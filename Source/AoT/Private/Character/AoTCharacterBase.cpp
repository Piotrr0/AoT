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

void AAoTCharacterBase::InitDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultAttributes, 1.f);
}

void AAoTCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAoTCharacterBase::InitAbilityActorInfo()
{

}

void AAoTCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float Level) const
{
	FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpec = GetAbilitySystemComponent()->MakeOutgoingSpec(Effect, Level, EffectContext);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
}
