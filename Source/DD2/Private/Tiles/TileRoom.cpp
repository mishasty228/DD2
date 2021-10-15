// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/TileRoom.h"

#include <string>


ATileRoom::ATileRoom()
{
	PrimaryActorTick.bCanEverTick = true;
	spawnParams.Owner = this;
	spawnLocation = this->GetActorLocation(); 
}

void ATileRoom::GenerateRoom(int32 sideSize)
{
	 for(int32 i = 0; i<=sideSize+1;i++)
	 {
	 	GenerateRow(sideSize+i);
	 	currentOffset.X+=offsetX;
	 	currentOffset.Y-=offsetY;
	 	spawnLocation=currentOffset+this->GetActorLocation();
	 }
	currentOffset.Y+=offsetY*2;
	spawnLocation=currentOffset+this->GetActorLocation();
	for(int32 i = sideSize*2+1; i > sideSize;i--)
	{
		GenerateRow(i-1);
		currentOffset.X+=offsetX;
		currentOffset.Y+=offsetY;
		spawnLocation=currentOffset+this->GetActorLocation();
	}
	AllTilesCheckNeighs();
}

void ATileRoom::GenerateRow(int32 rowLength)
{
	if(TileToSpawn)
	{
		for(int32 i = 0; i < rowLength+2; i++)
		{
					
			ATileBase* CurrentTile = GetWorld()->SpawnActor<ATileBase>(TileToSpawn, spawnLocation, rotator, FActorSpawnParameters());
			CurrentTile->TilesStruct.TileType=ETT_Path;
			CurrentTile->TilesStruct.r=currentRow;
			CurrentTile->TilesStruct.q=i;
			TilesArray.Add(CurrentTile);
			//CheckToSpawn NoneTile
			if (currentRow==0 || currentRow==size*2+2 || i == 0 || i == rowLength+1)
			{
				CurrentTile->TilesStruct.TileType=ETT_None;
			}
			//CheckToSpawn WallTile
			else if (currentRow==1 || currentRow==size*2+1 || i == 1 || i == rowLength)
			{
				CurrentTile->TilesStruct.TileType=ETT_Wall;
			}
			//RandomCheck for MissingTile in the middle
			else if (((currentRow > 2 && currentRow < size*2-2)||(i>size/2+1&&i<rowLength-size/2-1))&&hasLake)
			{
				if(FMath::FRandRange(0,1)>0.7f)
				{
					CurrentTile->TilesStruct.TileType=ETT_None;
					hasLake=false;
				}
			}
			spawnLocation.Y+=offsetY*2.0f;
			//UE_LOG(LogTemp, Display, TEXT("Row is %d /nCurrent offset is %s"),currentRow , *spawnLocation.ToString());
		}
		currentRow++;
	}
}

void ATileRoom::AllTilesCheckNeighs()
{
	for (ATileBase* Tile : TilesArray)
	{
		Tile->TilesStruct.aind = CoordToIndex(Tile->TilesStruct.r, Tile->TilesStruct.q);
		if (Tile->TilesStruct.TileType!=ETT_None)
		{
			SetTileNeighs(Tile);
			//UE_LOG(LogTemp, Display, TEXT("Tile %s checked neighs"),*Tile->GetName());
		}
	}
}

  ////////////////////////////////////////////////////////////////////
 ///Определение индекса в массиве с помощью координат шестигранника//
////////////////////////////////////////////////////////////////////
int32 ATileRoom::CoordToIndex(int32 r, int32 q)
{
	UE_LOG(LogTemp, Display, TEXT("Coordinate %d , %d"), r , q);

	int32 istep = size+2;
	int32 index = 0;
	for(int32 i = 0; i < r; i++)
	{
		index+=istep;
		if(i<size+1)
			{
				istep++;
			}
		else if (i>=size+1)  
			{
				istep--;
			}
		//UE_LOG(LogTemp, Display, TEXT("Index is %d"), index);
	}
	index+=q;
	//UE_LOG(LogTemp, Display, TEXT("Final index is %d"), index);
	return index;
}

void ATileRoom::SetTileNeighs(ATileBase* Tile)
{
	TArray<FVector2D> Dirs;
	if (Tile->TilesStruct.r<size+1) Dirs.Append(upHalfDirs, UE_ARRAY_COUNT(upHalfDirs));
	else Dirs.Append(downHalfDirs,UE_ARRAY_COUNT(downHalfDirs));
	for(FVector2D vec : Dirs)
	{
		Tile->Neighs.Add(TilesArray[CoordToIndex(Tile->TilesStruct.r+vec.X, Tile->TilesStruct.q+vec.Y)]);
	}
}

void ATileRoom::BeginPlay()
{
	spawnLocation = this->GetActorLocation();
	Super::BeginPlay();
	GenerateRoom(size);
}

// Called every frame
void ATileRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}