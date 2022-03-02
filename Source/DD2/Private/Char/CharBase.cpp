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

void ACharBase::InitializeHero(TEnumAsByte<ECharType> Type)
{
	HeroType = Type;
	switch (HeroType)
	{
	case ECT_Knight:
		SetParameters(
		RandomStream.RandRange(33,38),
		RandomStream.RandRange(12,15),
		RandomStream.RandRange(3,5),
		RandomStream.RandRange(10,15),
		0.2f,
		0.05f,
		0.2f,
		0.2f,
		0.2f,
		0.3f,
		0.5f
		);
		break;
		
	case ECT_Spearman:
		SetParameters(
		RandomStream.RandRange(29,34),
		RandomStream.RandRange(10,13),
		RandomStream.RandRange(4,6),
		RandomStream.RandRange(10,15),
		0.15f,
		0.1f,
		0.15f,
		0.15f,
		0.2f,
		0.2f,
		0.3f
		);
		break;

	case ECT_Archer:
		SetParameters(
		RandomStream.RandRange(20,25),
		RandomStream.RandRange(5,8),
		RandomStream.RandRange(5,7),
		RandomStream.RandRange(10,15),
		0.1f,
		0.2f,
		0.2f,
		0.2f,
		0.2f,
		0.3f,
		0.1f
		);
		break;
		
	default:
		SetParameters(
		RandomStream.RandRange(30,35),
		RandomStream.RandRange(10,15),
		RandomStream.RandRange(3,7),
		RandomStream.RandRange(10,15),
		0.2f,
		0.2f,
		0.2f,
		0.2f,
		0.2f,
		0.2f,
		0.2f
		);
		break;
	}
	
}

void ACharBase::Move()
{
	Super::Move();
}



