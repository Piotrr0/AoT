// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/CombatInterface.h"
#include "AoTCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAoTAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UCharacterMovementComponent;

UCLASS()
class AOT_API AAoTCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAoTCharacterBase();
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void InitDefaultAttributes() const;
	void InitDefaultAbilities() const;
	void InitDefaultPassiveAbilities() const;

	UAoTAbilitySystemComponent* GetASC();

	/*Combat Interface*/
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& CombatSocketTag) const;
	virtual UCharacterMovementComponent* GetMovement_Implementation() const;


protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> Effect, float Level) const;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAoTAbilitySystemComponent> AoTAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> DefaultPassiveAbilities;

private:


};
