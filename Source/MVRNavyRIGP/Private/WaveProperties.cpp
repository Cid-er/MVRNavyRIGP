// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveProperties.h"
#include "GerstnerWaterWaves.h"


// Sets default values
AWaveProperties::AWaveProperties()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AWaveProperties::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWaveProperties::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWaveProperties::ReconfigureWaves(UGerstnerWaterWaves* Waves)
{
	Waves -> RecomputeWaves(true);	
}
