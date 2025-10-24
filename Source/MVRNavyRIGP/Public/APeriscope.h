// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "APeriscope.generated.h"

UCLASS(Blueprintable)
class MVRNAVYRIGP_API AAPeriscope : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AAPeriscope();

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

	void RaisePeriscope();
	void LowerPeriscope();
	void RotatePeriscope(float RotationAmount);

private:
	bool bIsRaised;
	bool bIsRaising;
	bool bIsLowering;

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
	AActor* PeriscopeCam;

	UPROPERTY(VisibleAnywhere)
	APlayerController* PlayerController;
	//issue with including CameraComponent header

};
