// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AoTCharacterBase.generated.h"

UCLASS()
class AOT_API AAoTCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAoTCharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
