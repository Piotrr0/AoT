// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AoTAbilitySystemComponent.h"
#include "AbilitySystem/AoTGameplayAbility.h"

void UAoTAbilitySystemComponent::AbilityActorInfoSet()
{

}

void UAoTAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilities)
{
	for (const auto& AbilityClass : GameplayAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1.f);
		if (const UAoTGameplayAbility* AoTGameplayAbility = Cast<UAoTGameplayAbility>(AbilitySpec.Ability))
		{
			for (const auto& InputTag : AoTGameplayAbility->InputTags)
			{
				AbilitySpec.DynamicAbilityTags.AddTag(InputTag);
			}
			GiveAbility(AbilitySpec);
		}
	}
}

void UAoTAbilitySystemComponent::AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& PassiveGameplayAbilities)
{
	for (const auto& AbilityClass : PassiveGameplayAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1.f);
		if (const UAoTGameplayAbility* AoTGameplayAbility = Cast<UAoTGameplayAbility>(AbilitySpec.Ability))
		{
			for (const auto& InputTag : AoTGameplayAbility->InputTags)
			{
				AbilitySpec.DynamicAbilityTags.AddTag(InputTag);
			}
			GiveAbilityAndActivateOnce(AbilitySpec);
		}
	}
}

void UAoTAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (AbilitySpec.IsActive())
			{
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
			}
		}
	}
}

void UAoTAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UAoTAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) && AbilitySpec.IsActive())
		{
			AbilitySpecInputReleased(AbilitySpec);
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
		}
	}
}

UGameplayAbility* UAoTAbilitySystemComponent::GetAbilityByTag(const FGameplayTag& AbilityTag)
{
	FScopedAbilityListLock ActiveScopeLoc(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		for (FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if (Tag.MatchesTag(AbilityTag))
			{
				return AbilitySpec.Ability.Get();
			}
		}
	}
	return nullptr;
}

UGameplayAbility* UAoTAbilitySystemComponent::GetAbilityInstanceByTag(const FGameplayTag& AbilityTag)
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		TArray<UGameplayAbility*> Instances = AbilitySpec.GetAbilityInstances();
		for (UGameplayAbility* Instance : Instances)
		{
			for (FGameplayTag Tag : Instance->AbilityTags)
			{
				if (Tag.MatchesTag(AbilityTag))
				{
					return Instance;
				}
			}
		}
	}
	return nullptr;
}