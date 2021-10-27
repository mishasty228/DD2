// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/TileCorridor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ATileCorridor::ATileCorridor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	//SphereStart->CreateDefaultSubobject<USphereComponent>("SphereStart");
	//SphereStart->SetSphereRadius(40);
	//SphereEnd->CreateDefaultSubobject<USphereComponent>("SphereEnd");
	//SphereEnd->SetSphereRadius(40);
	PrimaryActorTick.bCanEverTick = true;
	spawnParams.Owner = this;

}

void ATileCorridor::GenerateCorridor(int32 length)
{
	if(TileSpawn)
	{
		for(int32 i = 0; i < length;i++)
        {
        	for (int32 j = 0; j<3;j++)
        	{
        		ATileBase* CurrentTile = GetWorld()->SpawnActor<ATileBase>(TileSpawn,
        		FVector(coordsToSpawn[j].X+offsetDirs[sideDir].X*(i+1),
        			coordsToSpawn[j].Y+offsetDirs[sideDir].Y*(i+1), GetActorLocation().Z), rotator,
        			FActorSpawnParameters());
				if(j<2)
				{
					CurrentTile->TilesStruct.TileType=ETT_Wall;
					CurrentTile->TilesStruct.Available = false;
				}
        		else
        		{
        			CurrentTile->TilesStruct.TileType=ETT_Path;
        			CurrentTile->TilesStruct.Available = true;
        		}
        		//UE_LOG(LogTemp, Display, TEXT("J is %d"), j);
        		CurrentTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
        			true));
        	}
        }
		for (int32 j = 0; j<2;j++)
		{
			ATileBase* CurrentTile = GetWorld()->SpawnActor<ATileBase>(TileSpawn,
			FVector(coordsToSpawn[j].X+offsetDirs[sideDir].X*(length+1),
				coordsToSpawn[j].Y+offsetDirs[sideDir].Y*(length+1), GetActorLocation().Z), rotator,
				FActorSpawnParameters());

				CurrentTile->TilesStruct.TileType=ETT_Wall;
				CurrentTile->TilesStruct.Available = false;
			//UE_LOG(LogTemp, Display, TEXT("J is %d"), j);
			CurrentTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
				true));
		}
	}
	
	
}

// Called when the game starts or when spawned
void ATileCorridor::BeginPlay()
{
	Super::BeginPlay();
	//GenerateCorridor(corridorMinLength+(rand()%(corridorMaxLength-corridorMinLength+1)));
}

// Called every frame
void ATileCorridor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

