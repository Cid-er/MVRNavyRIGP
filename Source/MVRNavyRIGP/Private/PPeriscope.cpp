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
	bIsRaising = false;
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
}




//RAISE AND LOWER CALLERS
void APPeriscope::RaisePeriscope(const FInputActionValue& Value)
{
	bool IsPressed = Value.Get<bool>();

	if (!GetWorldTimerManager().IsTimerActive(LR_TimerHandle) && IsPressed)
	{
		GetWorldTimerManager().SetTimer(LR_TimerHandle, this, &APPeriscope::RaisePeriscopeHandler, GetWorld()->GetDeltaSeconds(), true);
	}
}

void APPeriscope::LowerPeriscope(const FInputActionValue& Value)
{
	bool IsPressed = Value.Get<bool>();

	if (!GetWorldTimerManager().IsTimerActive(LR_TimerHandle) && IsPressed)
	{
		GetWorldTimerManager().SetTimer(LR_TimerHandle, this, &APPeriscope::LowerPeriscopeHandler, GetWorld()->GetDeltaSeconds(), true);
	}
}




//RAISE AND LOWER HANDLERS
void APPeriscope::RaisePeriscopeHandler()
{
	FVector Location = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Raising Periscope"));

	if (!bIsRaised || !bIsRaising)
	{
		//switch to periscope camera view
		if (PlayerController && !bIsViewport)
		{
			PlayerController->SetViewTarget(this);
			bIsViewport = true;
		}

		//to enable switching
		if (bIsLowered || bIsLowering)
		{
			bIsLowered = false;
			bIsLowering = false;
		}

		bIsRaising = true;

		Location.Z += RaiseSpeed * GetWorldTimerManager().GetTimerElapsed(LR_TimerHandle);
		SetActorLocation(Location);

		if (Location.Z >= MaxHeight)
		{
			//set to max height
			Location.Z = MaxHeight;
			SetActorLocation(Location);

			//set booleans
			bIsRaised = true;
			bIsRaising = false;
		}
	}

	if (Location.Z == MaxHeight && GetWorldTimerManager().IsTimerActive(LR_TimerHandle))
	{
		//stop timer
		GetWorldTimerManager().ClearTimer(LR_TimerHandle);
	}
}

void APPeriscope::LowerPeriscopeHandler()
{
	FVector Location = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Lowering Periscope"));

	if (!bIsLowered || !bIsLowering)
	{
		//to enable switching
		if (bIsRaised || bIsRaising) 
		{
			bIsRaised = false;
			bIsRaising = false;
		}

		bIsLowering = true;
		
		Location.Z -= LowerSpeed * GetWorldTimerManager().GetTimerElapsed(LR_TimerHandle);
		SetActorLocation(Location);

		if (Location.Z <= MinHeight)
		{
			//set to min height
			Location.Z = MinHeight;
			SetActorLocation(Location);

			//set booleans
			bIsLowered = true;
			bIsLowering = false;

			if (PlayerController && MainCam && bIsViewport)
			{
				//switch back to main camera view
				PlayerController->SetViewTarget(MainCam);
				bIsViewport = false;
			}
		}
	}

	if (Location.Z == MinHeight && GetWorldTimerManager().IsTimerActive(LR_TimerHandle))
	{
		//stop timer
		GetWorldTimerManager().ClearTimer(LR_TimerHandle);
	}
}



//ROTATION FUNCTION
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
		EIC->BindAction(RaiseAction, ETriggerEvent::Triggered, this, &APPeriscope::RaisePeriscope);
		EIC->BindAction(LowerAction, ETriggerEvent::Triggered, this, &APPeriscope::LowerPeriscope);
	}
}


void APPeriscope::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// It's important to keep the call chain on EndPlay or you may end up with serious bugs or crashes
	Super::EndPlay(EndPlayReason);


	GetWorld()->GetTimerManager().ClearTimer(LR_TimerHandle);
}

