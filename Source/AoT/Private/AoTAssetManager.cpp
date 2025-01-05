// Fill out your copyright notice in the Description page of Project Settings.


#include "AoTAssetManager.h"
#include "AoTGameplayTags.h"
#include "AbilitySystemGlobals.h"

UAoTAssetManager& UAoTAssetManager::Get()
{
	UAoTAssetManager* AoTAssetManager = Cast<UAoTAssetManager>(GEngine->AssetManager);
	return *AoTAssetManager;
}

void UAoTAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FAoTGameplayTags::InitNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData();
}
