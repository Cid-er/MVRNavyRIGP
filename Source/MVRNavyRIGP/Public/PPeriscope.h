// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "PPeriscope.generated.h"

class UInputComponent;
class UCameraComponent;
class APlayerController;
class UInputMappingContext;
class UInputAction;

UCLASS(Blueprintable)
class MVRNAVYRIGP_API APPeriscope : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	APPeriscope();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Periscope")
	UCameraComponent* PeriscopeCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Periscope")
	float HeightRange;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RaisePeriscope();
	void LowerPeriscope();
	void RotatePeriscope(const FInputActionValue& Value);

private:
	bool bIsRaised;
	bool bIsRaising;
	bool bIsLowering;
	bool bIsViewport;

	float CurrentRotation;

	UPROPERTY(EditAnywhere)
	float RaiseSpeed;

	UPROPERTY(EditAnywhere)
	float LowerSpeed;

	float MaxHeight;
	float MinHeight;

	UPROPERTY(VisibleAnywhere)
	AActor* MainCam;

	UPROPERTY(VisibleAnywhere)
	APlayerController* PlayerController;

	//issue with including CameraComponent header

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* PeriscopeMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* RaiseAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LowerAction;
};
