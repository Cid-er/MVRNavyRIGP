// Fill out your copyright notice in the Description page of Project Settings.


#include "PPeriscope.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"

// Sets default values
APPeriscope::APPeriscope()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	PeriscopeCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PeriscopeCamera"));
	PeriscopeCamera->SetupAttachment(RootComponent);

	PeriscopeCamera->SetFieldOfView(50.0f);
	PeriscopeCamera->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = true;

	HeightRange = 300.0f;
	RaiseSpeed = 50.0f;
	LowerSpeed = 50.0f;
	CurrentRotation = GetActorRotation().Yaw;

	bIsRaised = false;
	bIsRaising = true;
	bIsLowering = false;
	bIsViewport = false;
}

// Called when the game starts or when spawned
void APPeriscope::BeginPlay()
{
	Super::BeginPlay();

	//Initialize variables
	PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		PlayerController->Possess(this);
		MainCam = PlayerController->GetViewTarget();

		//Set Mapping Context, should be handled elsewhere but for testing purposes it's here, add to function and call function from different class later
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInput = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (PeriscopeMC)
			{
				EnhancedInput->AddMappingContext(PeriscopeMC, 0);
			}
		}
	}
	else 
	{
		MainCam = nullptr;
	}

	FVector Location = GetActorLocation();
	MinHeight = Location.Z;
	MaxHeight = MinHeight + HeightRange;

}

// Called every frame
void APPeriscope::Tick(float DeltaTime)
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

void APPeriscope::RaisePeriscope()
{
	if (PlayerController && !bIsViewport)
	{
		PlayerController->SetViewTarget(this);
		bIsViewport = true;
	}

	bIsRaising = true;

	if (!bIsRaised)
	{
		FVector Location = GetActorLocation();
		Location.Z += RaiseSpeed * GetWorld()->GetDeltaSeconds();
		SetActorLocation(Location);

		if (Location.Z >= MaxHeight)
		{
			Location.Z = MaxHeight;
			SetActorLocation(Location);
			bIsRaised = true;
			bIsRaising = false;
		}
	}
}

void APPeriscope::LowerPeriscope()
{
	bIsLowering = true;

	if (bIsRaised)
	{
		FVector Location = GetActorLocation();
		Location.Z -= LowerSpeed * GetWorld()->GetDeltaSeconds();
		SetActorLocation(Location);

		if (Location.Z <= MinHeight)
		{
			Location.Z = MinHeight;
			SetActorLocation(Location);
			bIsRaised = false;
			bIsLowering = false;

			if (PlayerController && MainCam && bIsViewport)
			{
				PlayerController->SetViewTarget(MainCam);
				bIsViewport = false;
			}
		}
	}
}

void APPeriscope::RotatePeriscope(const FInputActionValue& Value) 
{
	const float InputValue = Value.Get<float>();

	if (GetController()) 
	{
		AddControllerYawInput(InputValue);
		UE_LOG(LogTemp, Warning, TEXT("miaimc"));
	}
}

// Called to bind functionality to input
void APPeriscope::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &APPeriscope::RotatePeriscope);
	}
}

