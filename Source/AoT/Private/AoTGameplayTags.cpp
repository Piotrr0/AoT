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

	GameplayTags.Events_LeftHookFired = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Events.LeftHookFired"), FString("Left Hook Fired"));
	GameplayTags.Events_RightHookFired = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Events.RightHookFired"), FString("Right Hook Fired"));
	GameplayTags.Events_LeftHookReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Events.LeftHookReleased"), FString("Left Hook Released"));
	GameplayTags.Events_RightHookReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Events.RightHookReleased"), FString("Right Hook Released"));
	GameplayTags.Events_StopBoosting = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Events.StopBoosting"), FString("Stop Boosting"));

	GameplayTags.Abilities_Hook = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Hook"), FString("Hook Ability"));
	GameplayTags.Abilities_Boost = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Boost"), FString("Boost Ability"));
	GameplayTags.Abilities_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Jump"), FString("Jump Ability"));

}
