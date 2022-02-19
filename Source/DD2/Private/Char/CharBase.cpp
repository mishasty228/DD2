// Fill out your copyright notice in the Description page of Project Settings.


#include "Char/CharBase.h"

// Sets default values
ACharBase::ACharBase()
{	
 	// Set this character to call Tick() every frame.
 	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	Scene->SetupAttachment(this->GetMesh());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 1500;
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


// Called to bind functionality to input
void ACharBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharBase::InitializeHero()
{
	switch (HeroType)
	{
	case ECT_Knight:
		
		break;
	default: break;
	}
	
}



