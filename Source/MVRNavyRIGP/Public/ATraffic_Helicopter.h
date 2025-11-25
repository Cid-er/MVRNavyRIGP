// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ATraffic.h"
#include "ATraffic_Helicopter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MVRNAVYRIGP_API AATraffic_Helicopter : public AATraffic
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AATraffic_Helicopter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
