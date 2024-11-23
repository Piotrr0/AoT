// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AoTCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class AOT_API AAoTCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAoTCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	TObjectPtr<USpringArmComponent> CameraBoom;
	TObjectPtr<UCameraComponent> FollowCamera;


public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
