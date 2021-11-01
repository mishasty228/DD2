// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/TileMap.h"

// Sets default values
ATileMap::ATileMap()
{
	spawnParams.Owner = this;
	RandStream=FRandomStream(seed);
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	spawnLocation = this->GetActorLocation();
}

void ATileMap::DunGenMain()
{
	RandStreamGen();
	GenerateAllIndexes();
	AllRoomsSetup();
	WallsAndPathStarts();
}

void ATileMap::GenerateAllIndexes()
{
	for (int32 i = 0; i < worldSize; i++)
	{
		posX = i;
		for (int32 j = 0; j < worldSize; j++)
		{
			posY = j;
			if(TileToSpawn)
			{
				spawnLocation = this->GetActorLocation();
				spawnLocation+=FVector(offsetX*i,offsetY*j*2-offsetY*i,0);
				ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileToSpawn,
				spawnLocation, rotator,	FActorSpawnParameters());
				CurTile->TilesStruct.r=i;
				CurTile->TilesStruct.q=j;
				CurTile->TilesStruct.Available = false;
				CurTile->TilesStruct.TileType = ETT_None;
				Tiles.Add(CurTile);
			}
		}
	}
	TempArraysSetup();
}

void ATileMap::TempArraysSetup()
{
	TilesBackup.Empty();
	TilesBackup.Append(Tiles);
	TilesTemp.Empty();
	TilesTemp.Append(TilesBackup);
	TilesTempBackup.Empty();
	TilesTempBackup.Append(TilesTemp);
}

void ATileMap::RandStreamGen()
{
	if (seed==0)
	{
		RandStream.GenerateNewSeed();
		seed=RandStream.GetCurrentSeed();
	}
	else RandStream = FRandomStream(seed);
}

void ATileMap::AllRoomsSetup()
{
	TempArraysSetup();
	for (int32 i = 0; i<roomAmount;i++)
	{
		for (int32 j = 0; j<triesToPlaceARoom;j++)
		{
			if (GenerateRoom()) break;
		}
	}
	if(!CheckSpawnDespawn()) AllRoomsSetup();
	else Tiles = TilesBackup;
}

void ATileMap::WallsAndPathStarts()
{
	for(int32 i = 0; i < worldSize;i++)
	{
		for (int32 j = 0; j < worldSize; j++)
		{
			if (Tiles[i*worldSize+j]->TilesStruct.TileType==ETT_None)
			{
				if(i%2==1 && j%2==1)
				{
					Tiles[i*worldSize+j]->TilesStruct.TileType=ETT_Wall;
				}
				else if(i%2==0 && j%2==0)
				{
					Tiles[i*worldSize+j]->TilesStruct.TileType=ETT_PathStart;
					PathStartIndexes.Add(i*worldSize+j);
				}
			}
		}
	}
	
}

////////////////////////////////////////////////////
/////////////Check walls properly sets//////////////
////////////////////////////////////////////////////

bool ATileMap::GenerateRoom()
{

	TilesBackup.Empty();
	TilesBackup.Append(TilesTemp);
	TilesTemp.Empty();
	TilesTemp.Append(TilesTempBackup);


	bool success = true;
	
	int32 size = RandomOdd(minRoomSize,maxRoomSize);
	int32 startX = RandomOdd(1, worldSize-(size*2-1)-1);
	int32 startY = RandomOdd(1, worldSize-(size*2-1)-1);
	bool up = true;
	int32 start = startY;
	int32 end = startY+size;

	UE_LOG(LogTemp, Display, TEXT("SideSize is %d"), size);
	UE_LOG(LogTemp, Display, TEXT("StartX is %d"), startX);
	UE_LOG(LogTemp, Display, TEXT("StartY is %d"), startY);
	///First double loops check second double loops spawn if not overlap
	for (int32 i = startX; i < (startX+(size*2-1)); i++)
	{
		for(int32 j = start; j < end; j++)
		{
			tileIndex = worldSize*i+j;
			if (TilesTempBackup[tileIndex]->TilesStruct.TileType!=ETT_None)
            {
            	success=false;
            	UE_LOG(LogTemp, Display, TEXT("Index %d is colliding"), tileIndex);
            	break;
            }
			if((j==start||j==end-1)||(i==startX||i==startX+size*2-2))
			{
				TilesTemp[tileIndex]->TilesStruct.TileType=ETT_Wall;
				//UE_LOG(LogTemp, Display, TEXT("Index %d is Wall"), tileIndex);
			}
			else if((j>start||j<end-1)||(i>startX||i<startX+size*2-2))
			{
				TilesTemp[tileIndex]->TilesStruct.TileType=ETT_Room;
				//UE_LOG(LogTemp, Display, TEXT("Index %d is Room"), tileIndex);
			}
			
			if (!success) break;
		}
		if (!success) break;
		if(i<startX+size-1) end++;
		else start++;
	}
	if(!success)
	{
		TilesTemp.Empty();
		TilesTemp.Append(TilesTempBackup);
	}
	else
	{
		TilesTempBackup.Empty();
		TilesTempBackup.Append(TilesTemp);
		TilesBackup.Empty();
		TilesBackup.Append(TilesTempBackup);
	}
	return success;
}

bool ATileMap::CheckSpawnDespawn()
{
	bool allSet = true;
	return allSet;
}

int32 ATileMap::RandomOdd(int32 Min, int32 Max)
{
	int32 result = RandStream.FRandRange(Min,Max);
	if (result%2==0) result++;
	return result;
}

// Called when the game starts or when spawned
void ATileMap::BeginPlay()
{
	Super::BeginPlay();
	RandStreamGen();
	DunGenMain();
	/*GenerateAllIndexes();
	TempArraysSetup();
	GenerateRoom();*/
}

// Called every frame
void ATileMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

