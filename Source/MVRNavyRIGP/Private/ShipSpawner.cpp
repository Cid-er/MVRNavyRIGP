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
	pickBehaviour();
}

// Called every frame
void AShipSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	behaviourUpdate();
}

void AShipSpawner::RandomiseShip()
{
	//Make a new random seed and generate a random ID number.
	srand(time(0));
	int shipChoice = rand() % shipList.Num();
	//Look at the map to find which mesh to change to.
	const TCHAR* shipPath = *shipList[shipChoice];
	shipName = shipPath;

	//Load in the new mesh via it's path.
	UStaticMesh* MeshAsset = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, shipPath));

	//Get our current mesh, then set it to the new mesh.
	UStaticMeshComponent* ourMesh = GetComponentByClass<UStaticMeshComponent>();
	ourMesh->SetStaticMesh(MeshAsset);

	//Generate a new location and set our actor to it.
	FVector randomLocation(FMath::FRandRange(-750.0, 750.0), FMath::FRandRange(-750.0, 750.0), 300);
	SetActorLocation(randomLocation);
}

void AShipSpawner::pickBehaviour()
{
	//Make a random seed and generate a random number.
	srand(time(0));
	int behaviourChoice = rand() % 2;
	switch (behaviourChoice)
	{
		case 0:
			behaviour = 0;
			break;
		case 1:
			behaviour = 1;
			break;
		default:
			behaviour = 0;
			break;
	}
}

void AShipSpawner::behaviourUpdate()
{
	//If the behaviour is 0, stay stationary.
	if (behaviour == 0)
	{
		//No code to update movement as it is stationary
	}
	//If the behaviour is 1, move forward in a straight line.
	else if (behaviour == 1)
	{
		//Move in a straight line.
		AddActorWorldOffset(GetActorForwardVector() * speed * DeltaTime);
	}
}

