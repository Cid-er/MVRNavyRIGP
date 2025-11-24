// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnedShip.generated.h"

UCLASS()
class MVRNAVYRIGP_API ASpawnedShip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnedShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RandomiseShip();
	void LoadShips();
	//Value[0] is the path to the ships static mesh.
	//Value[1] is the path to the ships information
	TMap<uint32, TTuple<FString, FString>> shipList;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
