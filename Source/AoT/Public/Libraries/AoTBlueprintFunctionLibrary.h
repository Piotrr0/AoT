// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AoTBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AOT_API UAoTBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category = "AoTBlueprintFunctionLibrary|Input")
	static FVector2D GetHookFireStatus(const UObject* WorldContextObject);
};
