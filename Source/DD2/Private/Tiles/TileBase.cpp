// Fill out your copyright notice in the Description page of Project Settings.

#include "Tiles/TileBase.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"




// Sets default values
ATileBase::ATileBase()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	AdditionalMesh = CreateDefaultSubobject<UStaticMeshComponent>("AddMesh");
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Scene = CreateDefaultSubobject<USceneComponent>("Scene");
	SphereToCheckNeighs = CreateDefaultSubobject<USphereComponent>("SphereToCheckNeighs");
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Mesh;

	AdditionalMesh->SetupAttachment(Mesh);
	AdditionalMesh->SetRelativeLocation(FVector(0,0,0));
	Sphere->SetupAttachment(Mesh);
	Sphere->SetRelativeLocation(FVector(0,0,0));
	Scene->SetupAttachment(Mesh);
	Scene->SetRelativeLocation(FVector(0,0,20));
	SphereToCheckNeighs->SetupAttachment(Mesh);
	SphereToCheckNeighs->SetRelativeLocation(FVector(0,0,0));

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ATileBase::OnStep);
	Sphere->SetSphereRadius(40);
	SphereToCheckNeighs->OnComponentBeginOverlap.AddDynamic(this, &ATileBase::OnSideSphereOverlap);
	SphereToCheckNeighs->SetSphereRadius(200);
	
}

void ATileBase::OnStep(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
}

void ATileBase::OnSideSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	
}


void ATileBase::CheckNeighs()
{
	TArray<AActor*> overlap;
	//SphereToCheckNeighs->
	GetOverlappingActors(overlap);

	for (AActor* actor : overlap)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s casting"), *actor->GetName());
		ATileBase* OverlappedTile = Cast<ATileBase>(actor);
		if (OverlappedTile && OverlappedTile!=this)
		{
			Neighs.Add(OverlappedTile);
			//UE_LOG(LogTemp, Display, TEXT("Tile %s is a %s neighbour"), *OverlappedTile->GetName(), *this->GetName());
		}
	}
}


void ATileBase::CheckAvailableNeighs()
{
	for (int i = 0; i < Neighs.Num();i++)
	{
		if(Neighs[i]->TilesStruct.Available) AvailableNeighs.Add(Neighs[i]);
	}
}



// Called when the game starts or when spawned
void ATileBase::BeginPlay()
{
	Super::BeginPlay();
	
	MIDynamic = Mesh->CreateAndSetMaterialInstanceDynamic(0);
}

// Called every frame
void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileBase::SetMatScalarParameter(FName Name, float Value)
{
	if (MIDynamic) MIDynamic->SetScalarParameterValue(Name, Value);
}

bool ATileBase::CharInteraction_Implementation(ACharBase* Char)
{
	switch (TilesStruct.TileType)
	{
	case ETT_Path:
	case ETT_Door:
	case ETT_Room:
	case ETT_Spawn:
	case ETT_Portal:
	case ETT_Trap:
		Char->CurIndex= this->TilesStruct.aind;
		return true;
		break;
	default:
		return false;
		break;
	}
}

void ATileBase::SetMatVectorParameter(FName Name, FLinearColor Value)
{
	if (MIDynamic) MIDynamic->SetVectorParameterValue(Name,Value);
}

