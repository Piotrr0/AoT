// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AoTAbilitySystemComponent.h"

void UAoTAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& AbilitiesToGrant)
{
    for (const TSubclassOf<UGameplayAbility>& Ability : AbilitiesToGrant)
    {
        GiveAbility(FGameplayAbilitySpec(Ability, 1.f));
    }
}

void UAoTAbilitySystemComponent::InitDefaultAttributes(const TSubclassOf<UGameplayEffect>& AttributeEffect)
{
    check(AttributeEffect);
    const FGameplayEffectContextHandle ContextHandle = MakeEffectContext();
    const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingSpec(AttributeEffect, 1.f, ContextHandle);
    ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
