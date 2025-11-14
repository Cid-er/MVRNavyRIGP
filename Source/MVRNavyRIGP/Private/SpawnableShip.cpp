// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableShip.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASpawnableShip::ASpawnableShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnableShip::BeginPlay()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube"));
	UStaticMesh* shipType = MeshAsset.Object;

	UStaticMeshComponent* ourMesh = GetComponentByClass<UStaticMeshComponent>();
	ourMesh->SetStaticMesh(shipType);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("CodeHasRun"));

	Super::BeginPlay();
	
}

// Called every frame
void ASpawnableShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

