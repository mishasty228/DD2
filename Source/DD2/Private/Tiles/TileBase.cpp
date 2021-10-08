// Fill out your copyright notice in the Description page of Project Settings.

#include "Tiles/TileBase.h"




// Sets default values
ATileBase::ATileBase()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Mesh;
	Sphere->SetupAttachment(Mesh);
	Scene->SetupAttachment(Mesh);
	Scene->SetRelativeLocation(FVector(0,0,20));

	
}

// Called when the game starts or when spawned
void ATileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

