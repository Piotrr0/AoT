// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Rope.h"
#include "Kismet/KismetMathLibrary.h"

ARope::ARope()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARope::SetRopeTransform(const FVector& StartLocation, const FVector& EndLocation)
{
	const float Distance = FVector::Distance(StartLocation, EndLocation);
	const FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation);
	SetActorLocation(StartLocation);
	SetActorScale3D(FVector((Distance/200.f), 0.1f, 0.1f));
	SetActorRotation(Rotation);
}

void ARope::BeginPlay()
{
	Super::BeginPlay();
}
