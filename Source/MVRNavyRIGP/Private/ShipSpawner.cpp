// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipSpawner.h"

// Sets default values
AShipSpawner::AShipSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShipSpawner::BeginPlay()
{
	Super::BeginPlay();
	shipList.Add(0, "/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube");
	shipList.Add(1, "/Game/LevelPrototyping/Meshes/SM_Cylinder.SM_Cylinder");
	RandomiseShip();
}

// Called every frame
void AShipSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShipSpawner::RandomiseShip()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CodeHasRun"));
	srand(time(0));
	int shipChoice = rand() % 2;
	const TCHAR* shipPath = *shipList[shipChoice];

	UStaticMesh* MeshAsset = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, shipPath));

	UStaticMeshComponent* ourMesh = GetComponentByClass<UStaticMeshComponent>();
	ourMesh->SetStaticMesh(MeshAsset);
}

