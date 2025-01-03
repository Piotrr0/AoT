// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AoTCharacter.h"
#include "Player/AoTPlayerState.h"
#include "AbilitySystem/AoTAbilitySystemComponent.h"

AAoTCharacter::AAoTCharacter()
{

}

void AAoTCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

void AAoTCharacter::InitAbilityActorInfo()
{
	AAoTPlayerState* AoTPlayerState = Cast<AAoTPlayerState>(GetPlayerState());
	AoTPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AoTPlayerState, this);

	AbilitySystemComponent = AoTPlayerState->GetAbilitySystemComponent();
	AttributeSet = AoTPlayerState->GetAttributeSet();
	InitDefaultAttributes();
}
