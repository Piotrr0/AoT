// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/TraceToLocation.h"

UTraceToLocation* UTraceToLocation::CreateTraceToLocation(UGameplayAbility* OwningAbility, const FVector& Start, const FVector& End)
{
	UTraceToLocation* Task = NewAbilityTask<UTraceToLocation>(OwningAbility);
	Task->TraceStart = Start;
	Task->TraceEnd = End;
	return Task;
}

void UTraceToLocation::Activate()
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility);

	ValidData.Broadcast(HitResult);
	EndTask();
}
