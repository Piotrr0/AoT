// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AoTAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class AOT_API UAoTAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();
	UFUNCTION(BlueprintCallable)
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& GameplayAbilities);

	UFUNCTION(BlueprintCallable)
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& PassiveGameplayAbilities);

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	UGameplayAbility* GetAbilityByTag(const FGameplayTag& AbilityTag);
	UGameplayAbility* GetAbilityInstanceByTag(const FGameplayTag& AbilityTag);

};
