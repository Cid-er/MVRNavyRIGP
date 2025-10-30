// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "CDesktopCharacter.generated.h"

UCLASS()
class MVRNAVYRIGP_API ACDesktopCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACDesktopCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UInputMappingContext* PeriscopeMC;
	//UInputMappingContext* PlayerMC;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
