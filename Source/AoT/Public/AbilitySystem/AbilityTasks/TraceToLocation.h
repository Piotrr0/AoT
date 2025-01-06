// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TraceToLocation.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetDataSignature, const FHitResult&, Data);

/**
 * 
 */
UCLASS()
class AOT_API UTraceToLocation : public UAbilityTask
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "TraceToLocation", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UTraceToLocation* CreateTraceToLocation(UGameplayAbility* OwningAbility, const FVector& Start, const FVector& End);

	UPROPERTY(BlueprintAssignable)
	FTargetDataSignature ValidData;

	virtual void Activate() override;

private:

	FVector TraceStart; 
	FVector TraceEnd;
	
};
