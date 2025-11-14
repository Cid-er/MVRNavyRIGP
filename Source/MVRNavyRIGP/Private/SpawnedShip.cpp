// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnedShip.h"
#include "Components/StaticMeshComponent.h"

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
	RandomiseShip();
	
}

// Called every frame
void ASpawnedShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CodeHasRun"));
}

void ASpawnedShip::RandomiseShip()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CodeHasRun"));
	UStaticMesh* MeshAsset = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube")));

	UStaticMeshComponent* ourMesh = GetComponentByClass<UStaticMeshComponent>();
	ourMesh->SetStaticMesh(MeshAsset);
}

void ASpawnedShip::LoadShips()
{
	
}

