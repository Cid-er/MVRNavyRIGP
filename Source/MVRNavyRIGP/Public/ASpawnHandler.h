// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASpawnHandler.generated.h"

class AATraffic;
class AATraffic_Helicopter;

UCLASS()
class MVRNAVYRIGP_API AASpawnHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AASpawnHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnTraffic();

	//Array of traffic types to spawn, can be edited in derived blueprint editor
	UPROPERTY(EditAnywhere, Category = "Traffic")
	TArray<TSubclassOf<AATraffic>> TrafficTypes;

	//AActor* Submarine will be used when we have a submarine instead of PlayerPosition
	FVector PlayerPosition;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
