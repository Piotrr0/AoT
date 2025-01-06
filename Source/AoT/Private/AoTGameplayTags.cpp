// Fill out your copyright notice in the Description page of Project Settings.


#include "AoTGameplayTags.h"
#include "GameplayTagsManager.h"

FAoTGameplayTags FAoTGameplayTags::GameplayTags;

void FAoTGameplayTags::InitNativeGameplayTags()
{
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("Input for LMB"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("Input for RMB"));

	GameplayTags.CombatSocket_LeftGear = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftGear"), FString("Left Gear SocketTag"));
	GameplayTags.CombatSocket_RightGear = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightGear"), FString("Right Gear SocketTag"));
}
