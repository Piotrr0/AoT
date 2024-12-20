// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AoTCharacterBase.h"

AAoTCharacterBase::AAoTCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAoTCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AAoTCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
