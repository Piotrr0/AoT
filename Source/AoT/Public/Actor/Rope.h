// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rope.generated.h"

UCLASS()
class AOT_API ARope : public AActor
{
	GENERATED_BODY()
	
public:	
	ARope();

	void SetRopeTransform(const FVector& StartLocation, const FVector& EndLocation);

protected:
	virtual void BeginPlay() override;
};
