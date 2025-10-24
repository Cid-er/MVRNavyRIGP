// Fill out your copyright notice in the Description page of Project Settings.


#include "APeriscope.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAPeriscope::AAPeriscope()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//PeriscopeCam->CreateDefaultSubobject<UCameraComponent>(TEXT("PeriscopeCamera"));
	PeriscopeCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PeriscopeCamera"));
	RootComponent = PeriscopeCamera;

	PeriscopeCamera->SetFieldOfView(50.0f);
	PeriscopeCamera->bUsePawnControlRotation = true;

	HeightRange = 300.0f;
	RaiseSpeed = 50.0f;
	LowerSpeed = 50.0f;
	CurrentRotation = 0.0f;

	bIsRaised = false;
	bIsRaising = true;
	bIsLowering = false;
}

// Called when the game starts or when spawned
void AAPeriscope::BeginPlay()
{
	Super::BeginPlay();

	//Initialize variables
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		MainCam = PlayerController->GetViewTarget();
	}
	else {
		MainCam = nullptr;
	}

	FVector Location = GetActorLocation();
	MinHeight = Location.Z;
	MaxHeight = MinHeight + HeightRange;

}

// Called every frame
void AAPeriscope::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsRaised && !bIsLowering)
	{
		RaisePeriscope();
	}
	if (bIsRaised && !bIsRaising)
	{
		LowerPeriscope();
	}
}

void AAPeriscope::RaisePeriscope()
{
	bIsRaising = true;

	if (!bIsRaised)
	{
		FVector Location = GetActorLocation();
		Location.Z += RaiseSpeed * GetWorld()->GetDeltaSeconds();
		SetActorLocation(Location);
		PlayerController->SetViewTarget(this);

		if (Location.Z >= MaxHeight)
		{
			Location.Z = MaxHeight;
			SetActorLocation(Location);
			bIsRaised = true;
			bIsRaising = false;
		}
	}
}

void AAPeriscope::LowerPeriscope()
{
	bIsLowering = true;

	if (bIsRaised)
	{
		FVector Location = GetActorLocation();
		Location.Z -= LowerSpeed * GetWorld()->GetDeltaSeconds();
		SetActorLocation(Location);
		PlayerController->SetViewTarget(this);

		if (Location.Z <= MinHeight)
		{
			Location.Z = MinHeight;
			SetActorLocation(Location);
			bIsRaised = false;
			bIsLowering = false;
			if (PlayerController && MainCam) {
				PlayerController->SetViewTarget(MainCam);
			}
		}
	}
}

void AAPeriscope::RotatePeriscope(float RotationAmount)
{
	CurrentRotation += RotationAmount;
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = CurrentRotation;
	SetActorRotation(NewRotation);
}


