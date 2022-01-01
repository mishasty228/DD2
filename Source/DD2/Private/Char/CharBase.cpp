// Fill out your copyright notice in the Description page of Project Settings.


#include "Char/CharBase.h"

// Sets default values
ACharBase::ACharBase()
{
	CharDataComponent = CreateDefaultSubobject<UCharDataComponent>("CharDataComponent");
	this->AddOwnedComponent(CharDataComponent);
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(this->GetMesh());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 500;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-45.0f, 60.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	
}

// Called when the game starts or when spawned
void ACharBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Mouse_Y", this, &ACharBase::Camera_YAxis);
	PlayerInputComponent->BindAction("SpringUp", IE_Pressed, this, &ACharBase::SpringUp);
	PlayerInputComponent->BindAction("SpringDown", IE_Pressed, this, &ACharBase::SpringDown);
	
	PlayerInputComponent->BindAction("CameraRotation", IE_Pressed, this, &ACharBase::SetCanRotateTrue);
	PlayerInputComponent->BindAction("CameraRotation", IE_Released, this, &ACharBase::SetCanRotateFalse);
}

void ACharBase::Camera_YAxis(float Value)
{
	if (CanRotate)
	{
		SpringArm->AddRelativeRotation(FRotator(0,Value,0));
	}
}

void ACharBase::SpringDown()
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength+25, 250.0f, 1000.0f);
}

void ACharBase::SpringUp()
{
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength-25, 250.0f, 1000.0f);
}

void ACharBase::SetPlayerController(ADD2PlayerController* controller)
{
	pc = controller;
}


