// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AoTCharacterBase.h"
#include "AbilitySystem/AoTAbilitySystemComponent.h"
#include "AoTGameplayTags.h"

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

void AAoTCharacterBase::InitDefaultAbilities() const
{
	UAoTAbilitySystemComponent* AoTASC = Cast<UAoTAbilitySystemComponent>(AbilitySystemComponent);
	check(AoTASC);
	AoTASC->AddCharacterAbilities(DefaultAbilities);
}

FVector AAoTCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& CombatSocketTag) const
{
	FAoTGameplayTags GameplayTags = FAoTGameplayTags::Get();

	if (CombatSocketTag == GameplayTags.CombatSocket_LeftGear)
	{
		return GetMesh()->GetSocketLocation("LeftGear_Socket");
	}
	else if (CombatSocketTag == GameplayTags.CombatSocket_RightGear)
	{
		return GetMesh()->GetSocketLocation("RightGear_Socket");
	}
	return FVector();
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
