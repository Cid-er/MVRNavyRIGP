// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnedShip.h"

// Sets default values
ASpawnedShip::ASpawnedShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnedShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnedShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

