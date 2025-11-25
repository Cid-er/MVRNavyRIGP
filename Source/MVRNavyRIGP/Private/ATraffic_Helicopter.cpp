// Fill out your copyright notice in the Description page of Project Settings.


#include "ATraffic_Helicopter.h"


AATraffic_Helicopter::AATraffic_Helicopter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UStaticMeshComponent* Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HelicopterMesh"));
	Root->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	RootComponent = Root;

	//set static mesh to a cube for testing purposes, change to helicopter mesh later
	//TrafficMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	//Root->SetStaticMesh(TrafficMesh);
}


// Sets default values
void AATraffic_Helicopter::BeginPlay()
{
	Super::BeginPlay();
	//TrafficMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Assets/KA - 27Blockout.KA - 27Blockout")));
	UStaticMeshComponent* ourMesh = GetComponentByClass<UStaticMeshComponent>();
	ourMesh->SetStaticMesh(TrafficMesh);
	ourMesh->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	//RootComponent->SetStaticMesh(TrafficMesh);
}
