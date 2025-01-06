// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/AoTBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AoTPlayerController.h"

FVector2D UAoTBlueprintFunctionLibrary::GetHookFireStatus(const UObject* WorldContextObject)
{
	if (const AAoTPlayerController* PlayerController = Cast<AAoTPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)))
	{
		return PlayerController->GetHookStatus();
	}
	return FVector2D::ZeroVector;
}
