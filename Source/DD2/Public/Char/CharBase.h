// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CharDataComponent.h"
#include "DD2PlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Living/LivingBeing.h"
#include "CharBase.generated.h"

class ADD2PlayerController;
class ATileBase;

UCLASS()
class DD2_API ACharBase : public ALivingBeing
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
	int32 CurIndex=0;

	TEnumAsByte<ECharType> HeroType = ECT_Knight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InitializeHero();
};


