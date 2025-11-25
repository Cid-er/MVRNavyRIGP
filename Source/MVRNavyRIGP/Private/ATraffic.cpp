// Fill out your copyright notice in the Description page of Project Settings.


#include "ATraffic.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AATraffic::AATraffic()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AATraffic::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AATraffic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

