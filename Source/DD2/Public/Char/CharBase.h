// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CharDataComponent.h"
#include "DD2PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "CharBase.generated.h"

class ADD2PlayerController;
class ATileBase;

UCLASS()
class DD2_API ACharBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharBase();

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Components")
	USceneComponent* Scene;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Components")
	UCameraComponent* Camera;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UCharDataComponent* CharDataComponent;

	bool CanRotate = false;
	
	ADD2PlayerController* pc;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Camera_YAxis(float Value);
	void SpringDown();
	void SpringUp();

	void SetPlayerController(ADD2PlayerController* controller);

	void SetCanRotateTrue()
	{
		CanRotate = true;
		if (pc)
		{
			pc->SetShowMouseCursor(false);
			pc->bCanSelect = false;
		}
	}	
	void SetCanRotateFalse()
	{
		CanRotate=false;
		if (pc)
		{
			pc->SetShowMouseCursor(true);
			pc->bCanSelect = true;
		}
	}
};
