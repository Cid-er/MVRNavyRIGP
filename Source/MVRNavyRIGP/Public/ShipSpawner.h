// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipSpawner.generated.h"

UCLASS()
class MVRNAVYRIGP_API AShipSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShipSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RandomiseShip();
	TMap<uint32, FString> shipList;

	FString shipName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
