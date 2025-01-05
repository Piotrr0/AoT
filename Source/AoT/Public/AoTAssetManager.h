// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AoTAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class AOT_API UAoTAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:

	static UAoTAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
