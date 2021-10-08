// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/TileRoom.h"

#include "../../../../../../EpicGamesGames/UE_4.27/Engine/Shaders/Private/PathTracing/Utilities/PathTracingRandomSequence.ush"


ATileRoom::ATileRoom()
{
	
	PrimaryActorTick.bCanEverTick = true;
	spawnParams.Owner = this;
	spawnLocation = this->GetActorLocation(); 
}

void ATileRoom::GenerateRoom(int32 sideSize)
{
	 for(int32 i = 0; i<=sideSize;i++)
	 {
	 	GenerateRow(sideSize+i);
	 	currentOffset.X+=offsetX;
	 	currentOffset.Y-=offsetY;
	 	spawnLocation+=currentOffset;
	 	
	 }
	for(int32 i = sideSize*2; i > sideSize;i++)
	{
		GenerateRow(i-sideSize);
		currentOffset.X+=offsetX;
		currentOffset.Y+=offsetY;
		spawnLocation+=currentOffset;
	}
	
}

void ATileRoom::GenerateRow(int32 rowLength)
{
	
	if(Tile)
	{
		for(int32 i = 0; i < rowLength+2; i++)
		{
			ATileBase* CurrentTile = world->SpawnActor<ATileBase>(Tile, spawnLocation, rotator, spawnParams);
			//CheckToSpawn NoneTile
			if (currentRow==0 || currentRow==size+2-1 || i == 0 || i == rowLength-1)
			{
				CurrentTile->TilesStruct.TileType=ETT_None;
			}
			//CheckToSpawn WallTile
			else if (currentRow==1 || currentRow==size+2-2 || i == 1 || i == rowLength-2)
			{
				CurrentTile->TilesStruct.TileType=ETT_Wall;
			}
			//RandomCheck for MissingTile in the middle
			else if ((currentRow > 2 && currentRow < size*2-3)||(i>2&&i<rowLength-3)&&hasLake)
			{
				if(FMath::FRandRange(0,1)>0.7f)
				{
					CurrentTile->TilesStruct.TileType=ETT_None;
				}
				hasLake=false;
			}
			spawnLocation.Y+=offsetY*2;
			UE_LOG(LogTemp, Display, TEXT("Current offset is %s"), spawnLocation);
		}
	}
}

void ATileRoom::BeginPlay()
{
	Super::BeginPlay();
	GenerateRoom(size);
}

// Called every frame
void ATileRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}