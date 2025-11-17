// Fill out your copyright notice in the Description page of Project Settings.


#include "ShipSpawner.h"

float speed = 1.0f; 
int behaviour;
int spinDir;

// Sets default values
AShipSpawner::AShipSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UStaticMeshComponent* createdMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATICMESH"));
	createdMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AShipSpawner::BeginPlay()
{
	Super::BeginPlay();
	shipList.Add(0, "/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube");
	shipList.Add(1, "/Game/LevelPrototyping/Meshes/SM_Cylinder.SM_Cylinder");
	RandomiseShip();
	randomiseBehaviour();
}

// Called every frame
void AShipSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (behaviour == 0) // behaviour when stationary
	{
		if (spinDir == 1) // left (Ignore 0, as 0 means no Rotation
		{
			FRotator rotation = GetActorRotation();
			rotation += FRotator(0, -1, 0) * 10.0f * DeltaTime;
			SetActorRotation(rotation);
		}
		if (spinDir == 2) // right
		{
			FRotator rotation = GetActorRotation();
			rotation += FRotator(0, 1, 0) * 10.0f * DeltaTime;
			SetActorRotation(rotation);
		}

	}
	if (behaviour == 1) // behaviour when moving
	{
		FVector movement = GetActorLocation();
		movement += GetActorForwardVector() * 50.0f * DeltaTime;
		SetActorLocation(movement);
		if (spinDir == 1) // left (Ignore 0, as 0 means no Rotation
		{
			FRotator rotation = GetActorRotation();
			rotation += FRotator(0, -1, 0) * 10.0f * DeltaTime;
			SetActorRotation(rotation);
		}
		if (spinDir == 2) // right
		{
			FRotator rotation = GetActorRotation();
			rotation += FRotator(0, 1, 0) * 10.0f * DeltaTime;
			SetActorRotation(rotation);
		}
	}
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

	//Generate a new rotation for the actor to look at and potential spin direction.
	FRotator randomRotation(0,FMath::FRandRange(-180.0, 180.0),0); 
	SetActorRotation(randomRotation);
	spinDir = rand() % 3;
}

void AShipSpawner::randomiseBehaviour()
{
	behaviour = rand() % 2;
}

