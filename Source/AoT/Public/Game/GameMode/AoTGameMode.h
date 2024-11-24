// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "AoTGameMode.generated.h"


class UCharacterClassInfo;

UCLASS()
class AOT_API AAoTGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UCharacterClassInfo* GetCharacterClassInfo();

private:

	TObjectPtr<UCharacterClassInfo> ClassDefaults;
};
