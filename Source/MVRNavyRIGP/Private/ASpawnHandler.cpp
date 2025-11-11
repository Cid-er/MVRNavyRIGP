// Fill out your copyright notice in the Description page of Project Settings.


#include "ASpawnHandler.h"
#include "ATraffic.h"
#include "ATraffic_Helicopter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AASpawnHandler::AASpawnHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AASpawnHandler::BeginPlay()
{
	Super::BeginPlay();

	//will get Submarine position later in development, currently gets player position
	PlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	//will call multiple times once more traffic types are added
	SpawnTraffic();
}

// Called every frame
void AASpawnHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AASpawnHandler::SpawnTraffic()
{
	if (TrafficTypes.Num() == 0) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No traffic types specified in SpawnHandler"));
		return;
	}

	TSubclassOf<AATraffic> TrafficClass = TrafficTypes[FMath::RandRange(0, TrafficTypes.Num() - 1)];

	//change player position to submarine position later
	FVector SubLocation = PlayerPosition;

	if (TrafficClass->IsChildOf(AATraffic_Helicopter::StaticClass())) 
	{
		FVector SpawnLocation;
		FRotator SpawnRotation;

		//Sets the distance at which the helicopter will spawn around the player
		float MinDistance = 37000.0f;
		float MaxDistance = 90000.0f;
		float Distance = FMath::RandRange(MinDistance, MaxDistance);

		//Sets the height at which the helicopter will spawn around the player
		float MinHeight = 12500.0f;
		float MaxHeight = 20000.0f;
		float Height = FMath::RandRange(MinHeight, MaxHeight);
		
		//Sets the angle at which the helicopter will spawn around the player
		float AngleFromPlayer = FMath::RandRange(0.0f, 360.0f);

		//parametric equations for circle to set the spawn location around player
		SpawnLocation = FVector(FMath::Cos(FMath::DegreesToRadians(AngleFromPlayer)) * (Distance + SubLocation.X), FMath::Sin(FMath::DegreesToRadians(AngleFromPlayer)) * (Distance + SubLocation.Y), Height);
		
		//Sets a random yaw rotation for the helicopter
		float YawRotation = FMath::RandRange(0.0f, 360.0f);
		SpawnRotation = FRotator(0.0f, YawRotation, 0.0f);

		//Spawn a helicopter traffic actor with helicopter spawn point boundaries
		GetWorld()->SpawnActor<AATraffic_Helicopter>(TrafficClass, SpawnLocation, SpawnRotation);
	}


//	else if(TrafficClass->IsChildOf(AATraffic_Ship::StaticClass()))
//	{
//		 Spawn a ship traffic actor with ship spawn point boundaries
//	}
}

