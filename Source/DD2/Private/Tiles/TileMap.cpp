// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/TileMap.h"

#include "Char/GameMaster.h"


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
	UE_LOG(LogTemp, Display, TEXT("Seed is %i"), seed);
	prevLocation = FVector2D(worldSize/2);
	GenerateAllIndexes();
	TempArraysSetup();
	RoomCorCycle();
	FinishRoomCorners();
	FindOptionalCorridors();
	FinishRoomCorners();
	SpawnEveryIndex();
}

//Indexes spawning

void ATileMap::SpawnEveryIndex()
{
	for (int32 i = 0; i < worldSize; i++)
	{
		posX = i;
		for (int32 j = 0; j < worldSize; j++)
		{
			posY = j;
			spawnLocation = this->GetActorLocation();
			spawnLocation+=FVector(offsetX*i,offsetY*j*2-offsetY*i,0);
			const FTilesStruct TilesStruct = FTilesStruct(i,j,i-j, CoordToIndex(FVector2D(i,j)));
			switch (TileTypes[i*worldSize+j])
			{
			case ETT_Room:
				if(TileBase)
				{
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileBase,
					spawnLocation, rotator,	FActorSpawnParameters());
					TilesStruct.Available = true;
					TilesStruct.TileType = TileTypes[i*worldSize+j];
					CurTile->TilesStruct = TilesStruct;
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Path:
				if(TileBase)
				{
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileBase,
					spawnLocation, rotator,	FActorSpawnParameters());
					TilesStruct.Available = true;
					TilesStruct.TileType = TileTypes[i*worldSize+j];
					CurTile->TilesStruct = TilesStruct;
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Door:
				if(TileDoor)
				{
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileDoor,
					spawnLocation, rotator,	FActorSpawnParameters());
					TilesStruct.Available = true;
					TilesStruct.TileType = TileTypes[i*worldSize+j];
					CurTile->TilesStruct = TilesStruct;
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Block:
				if(TileBlock)
				{
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileBlock,
					spawnLocation, rotator,	FActorSpawnParameters());
					TilesStruct.Available = false;
					TilesStruct.TileType = TileTypes[i*worldSize+j];
					CurTile->TilesStruct = TilesStruct;
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Wall:
				if(TileWall)
				{
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileWall,
					spawnLocation, rotator,	FActorSpawnParameters());
					CurTile->AdditionalMesh->AddWorldRotation(CheckWallRotation(i*worldSize+j));
					TilesStruct.Available = false;
					TilesStruct.TileType = TileTypes[i*worldSize+j];
					CurTile->TilesStruct = TilesStruct;
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Spawn:
				if(TileSpawner)
				{
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileSpawner,
					spawnLocation, rotator,	FActorSpawnParameters());
					TilesStruct.Available = true;
					TilesStruct.TileType = TileTypes[i*worldSize+j];
					CurTile->TilesStruct = TilesStruct;
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Portal:
				if(TileDespawner)
				{
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileDespawner,
					spawnLocation, rotator,	FActorSpawnParameters());
					TilesStruct.Available = true;
					TilesStruct.TileType = TileTypes[i*worldSize+j];
					CurTile->TilesStruct = TilesStruct;
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_EnemySpawn:
				if(TileEnemy)
				{
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileEnemy,
					spawnLocation, rotator,	FActorSpawnParameters());
					TilesStruct.Available = false;
					TilesStruct.TileType = TileTypes[i*worldSize+j];
					CurTile->TilesStruct = TilesStruct;
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Chest:
				if(TileChest)
				{
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileChest,
					spawnLocation, rotator,	FActorSpawnParameters());
					TilesStruct.Available = false;
					TilesStruct.TileType = TileTypes[i*worldSize+j];
					CurTile->TilesStruct = TilesStruct;
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Key:
				if(TileKey)
				{
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileKey,
					spawnLocation, rotator,	FActorSpawnParameters());
					TilesStruct.Available = true;
					TilesStruct.TileType = TileTypes[i*worldSize+j];
					CurTile->TilesStruct = TilesStruct;
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Shop:
				if(TileShop)
				{
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileShop,
					spawnLocation, rotator,	FActorSpawnParameters());
					TilesStruct.Available = false;
					TilesStruct.TileType = TileTypes[i*worldSize+j];
					CurTile->TilesStruct = TilesStruct;
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
				default:break;
			}
			/*if(TileBase&& (TileTypes[i*worldSize+j]!=ETT_None && TileTypes[i*worldSize+j]!=ETT_Last))
			{
				spawnLocation = this->GetActorLocation();
				spawnLocation+=FVector(offsetX*i,offsetY*j*2-offsetY*i,0);
				ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileBase,
				spawnLocation, rotator,	FActorSpawnParameters());
				CurTile->TilesStruct.r=i;
				CurTile->TilesStruct.q=j;
				CurTile->TilesStruct.Available = false;
				CurTile->TilesStruct.TileType = TileTypes[i*worldSize+j];
				Tiles.Add(CurTile);
				CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
				true));
			}*/
		}
	}
}

//Indexes setup 

void ATileMap::GenerateAllIndexes()
{
	TileTypes.Empty();
	for (int32 i = 0; i < worldSize; i++)
	{
		posX = i;
		for (int32 j = 0; j < worldSize; j++)
		{
			posY = j;
			if(TileBase)
			{
				/*spawnLocation = this->GetActorLocation();
				spawnLocation+=FVector(offsetX*i,offsetY*j*2-offsetY*i,0);
				ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileToSpawn,
				spawnLocation, rotator,	FActorSpawnParameters());
				CurTile->TilesStruct.r=i;
				CurTile->TilesStruct.q=j;
				CurTile->TilesStruct.Available = false;
				CurTile->TilesStruct.TileType = ETT_None;
				Tiles.Add(CurTile);*/
				if((i==0 || i ==worldSize-1)||(j==0||j==worldSize-1)) TileTypes.Add(ETT_Last);
				else TileTypes.Add(ETT_None);
			}
		}
	}
	TempArraysSetup();
}

void ATileMap::TempArraysSetup()
{
	TileTypesBackup.Empty();
	TileTypesBackup.Append(TileTypes);
	TileTypesTemp.Empty();
	TileTypesTemp.Append(TileTypesBackup);
	TileTypesTempBackup.Empty();
	TileTypesTempBackup.Append(TileTypesTemp);
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

ATileBase* ATileMap::FindTileByIndex(int32 index)
{
	ATileBase* IndexedTile = nullptr;
	//UE_LOG(LogTemp,Display,TEXT("Looking for tile with index %i"), index);
	for (ATileBase* Tile : Tiles)
	{
		if (Tile->TilesStruct.aind == index)
		{
			IndexedTile = Tile;
			break;
		}
	}
	return IndexedTile;
}

TArray<ATileBase*> ATileMap::FindTilesInRange(int32 index, int32 range)
{
	TArray<ATileBase*> Result;
	int32 dif = 0;
	const FVector2D Start = IndexToCoord(index);
	UE_LOG(LogTemp, Display, TEXT("Range %i"), range);
	for (int32 j = Start.X-range; j <= Start.X+range; j++, dif++)
	{
		UE_LOG(LogTemp, Display, TEXT("Row found %i"), j);
		for (int32 i = FMath::Min<int32>(Start.Y+dif, Start.Y+range);
			i >= FMath::Max<int32>(Start.Y-range, Start.Y-range-range+dif); i--)
		{
			UE_LOG(LogTemp, Display, TEXT("Col found %i"), i);
			ATileBase* Tile = FindTileByIndex(CoordToIndex(FVector2D(j,i)));
			if (Tile) Result.Add(Tile);
		}
	}
	return Result;
}

TArray<ATileBase*> ATileMap::FindTilesReachable(int32 index, int32 range)
{
	TArray<ATileBase*> Result;
	TArray<int32> Visited;
	TArray<int32> LastRun;
	TArray<int32> CurRun;
	const int32 start = index;

	Visited.Add(start);
	Result.Add(FindTileByIndex(start));
	LastRun.Add(start);
	
	for (int32 k = 1; k <= range; k++)
	{
		for (const int32 i : LastRun)
		{
			for (FVector2D N : NeighsIndexes)
			{
				int32 curInd = CoordToIndex(IndexToCoord(i)+N);
				ATileBase* CheckTile = FindTileByIndex(curInd);
				if (CheckTile && !Visited.Contains(curInd) && CheckTile->TilesStruct.Available)
				{
					//UE_LOG(LogTemp,Display,TEXT("Found available non-visited tile"));
					CheckTile->Distance=k;
					CurRun.Add(curInd);
					Visited.Add(curInd);
					Result.Add(CheckTile);
				}
			}
		}
		LastRun = CurRun;
		CurRun.Empty();
	}
	return Result;
}

TArray<int32> ATileMap::FindPathRoute(int32 A, int32 B)
{
	TArray<int32> Path;
	TArray<int32> openPath;
	TArray<int32> closedPath;

	int32 CurIndex = A;

	ATileBase* CurTile = FindTileByIndex(CurIndex);
	CurTile->G = 0;
	CurTile->H = GetDistance(CurIndex, B);
	CurTile->F = GetFDistance(A,CurIndex,B);
	openPath.Add(CurIndex);
	while (openPath.Num() != 0)
	{
		openPath = SortFG(openPath);
		CurIndex = openPath[0];
		CurTile = FindTileByIndex(CurIndex);
		openPath.Remove(CurIndex);
		closedPath.Add(CurIndex);
		UE_LOG(LogTemp,Display,TEXT("Added index %i to closedPath with G %i, H %i, F %i"), CurIndex, CurTile->G,
						CurTile->H, CurTile->F);

		const int32 g = FindTileByIndex(CurIndex)->G + 1;

		if (closedPath.Contains(B))
		{
			break;
		}

		for (FVector2D dir : NeighsIndexes)
		{
			int32 adTile = CoordToIndex(IndexToCoord(CurIndex) + dir);
			ATileBase* CheckTile = FindTileByIndex(adTile);
			if (CheckTile)
			{
				if (!CheckTile->TilesStruct.Available)
				{
					continue;
				}
				if (closedPath.Contains(adTile))
				{
					continue;
				}
				if (!openPath.Contains(adTile))
				{
					CheckTile->G = g;
					CheckTile->H = GetDistance(adTile, B);
					CheckTile->F = GetFDistance(A,adTile,B);
					openPath.Add(adTile);
					UE_LOG(LogTemp,Display,TEXT("Added index %i to openPath with G %i, H %i, F %i"), adTile, CheckTile->G,
						CheckTile->H, CheckTile->F);
				}
				else if (CheckTile->F > g + CheckTile->H)
				{
					CheckTile->G = GetDistance(A,adTile);
					UE_LOG(LogTemp,Display, TEXT("F>g+H so g = G"));
				}
			}
		}
	}

	if (closedPath.Contains(B))
	{
		CurIndex = B;
		UE_LOG(LogTemp, Display, TEXT("B index is %i"), CurIndex);
		Path.Add(CurIndex);
		for (int32 i = FindTileByIndex(B)->G-1; i >= 0; i--)
		{
			for (FVector2D dir : NeighsIndexes)
			{
				int32 adTile = CoordToIndex(IndexToCoord(CurIndex) + dir);
				const ATileBase* CheckTile = FindTileByIndex(adTile);
				if (CheckTile->G == i && closedPath.Contains(adTile))
				{
					UE_LOG(LogTemp, Display, TEXT("Path index is %i"), CurIndex);
					CurIndex = adTile;
					Path.Add(CurIndex);
					break;
				}
			}
		}
	}
	
	for (int32 i = 0; i < Path.Num()/2; i++)
	{
		Path.Swap(i,Path.Num()-1-i);
	}
	Path.RemoveAt(0);
	for (int32 i : Path) UE_LOG(LogTemp,Display,TEXT("%i "),i) ;
	return Path;
}

int32 ATileMap::GetDistance(int32 A, int32 B)
{
	const int32 dR = (IndexToCoord(B).X-IndexToCoord(A).X);
	const int32 dQ = (IndexToCoord(B).Y-IndexToCoord(A).Y);
	if (dR*dQ<0) return (FMath::Abs(dR)+FMath::Abs(dQ));
	return FMath::Max(FMath::Abs(dR),FMath::Abs(dQ));
}

int32 ATileMap::GetTDistance(int32 B)
{
	return FindTileByIndex(B)->Distance;
}

int32 ATileMap::GetFDistance(int32 A, int32 B, int32 C)
{
	return GetDistance(A, B) + GetDistance(B, C);
}

TArray<int32> ATileMap::SortFG(TArray<int32> indexes)
{
	TArray<int32> result = indexes;
	result.Sort([this](const int32 A, const int32 B)
	{
		return FindTileByIndex(A)->F < FindTileByIndex(B)->F;
	});
	result.Sort([this](const int32 A, const int32 B)
	{
		return FindTileByIndex(A)->G < FindTileByIndex(B)->G;
	});
	return result;
}

/**
 * @brief Generates room at certain location
 * @param roomnum Current number of rooms generated
 * @param size Size of one side of a room, so length or width of a room will be 2size-1
 * @param RoomType
 * @return true if not collided with any other room
 */
bool ATileMap::GenerateRoom(int32 roomnum, int32 size, TEnumAsByte<ERoomTypes> RoomType)
{
	
	TileTypesTemp.Empty();
	TileTypesTemp.Append(TileTypesBackup);
	TileTypesTempBackup.Empty();
	TileTypesTempBackup.Append(TileTypesTemp);
	
	bool success = true;
	bool spawned = false;
	
	TArray <int32> cornersTemp;

	if (size==0) size = RandomOdd(minRoomSize,maxRoomSize);
	//if (roomnum == roomAmount-1) size++;
	int32 startX = prevLocation.X;
	int32 startY = prevLocation.Y;
	
	//UE_LOG(LogTemp, Display, TEXT("ROOM is %d"), roomToSpawn);
	
	if (roomnum==0)
	{
		startX=prevLocation.X-size+1;
		startY=prevLocation.Y-size+1;
	}
	if (CurRoomType!=ERT_Base) RoomType = CurRoomType;
	FRoomStruct TempRoom = FRoomStruct(RoomType, size, FVector2D(startX,startY), RandomOdd(minEnemies, maxEnemies));
	//UE_LOG(LogTemp, Display, TEXT("ROOM %d is %d"), roomnum, RoomType.GetValue());

	int32 start = startY;
	int32 end = startY+size;
	
	nextLocation = FVector2D(startX,startY);
	
	//CornersOfRoomSetup
	for (FVector2D dir : NeighsIndexes)
	{
		//if (TileTypesTempBackup[CoordToIndex(FVector2D(startX+size-1, startY+size-1)+dir*(size-1))]==ETT_Wall)
		int32 IndToAdd = CoordToIndex(FVector2D(startX+size-1, startY+size-1)+dir*(size-1));
		cornersTemp.Add(IndToAdd);
		
	}

	//TempRoomSetup
	TempRoom.cornerInd.Append(cornersTemp);
	
	for (int32 i = startX; i < (startX+(size*2-1)); i++)
	{
		for(int32 j = start; j < end; j++)
		{
			tileIndex = worldSize*i+j;
			//UE_LOG(LogTemp, Display, TEXT("tileind %i %i %i"), tileIndex, i, j);
			if (TileTypesTempBackup[tileIndex]!=ETT_None&&TileTypesTempBackup[tileIndex]!=ETT_Wall)
			{
				//UE_LOG(LogTemp, Warning, TEXT("Room failed to generate because of collision at index %d"),tileIndex);
				success=false;
				//UE_LOG(LogTemp, Display, TEXT("Index %d is colliding"), tileIndex);
				break;
			}
			if((j==start||j==end-1)||(i==startX||i==startX+size*2-2))
			{
				TileTypesTemp[tileIndex]=ETT_Wall;
				//UE_LOG(LogTemp, Display, TEXT("Index %d is Wall"), tileIndex);
			}
			else if((j>start&&j<end-1)&&(i>startX&&i<startX+size*2-2))
			{
				TileTypesTemp[tileIndex]=ETT_Room;
				if((j>start+1&&j<end-2)&&(i>startX+1&&i<startX+size*2-3)) TempRoom.WayTilesArray.Add(tileIndex);
				//UE_LOG(LogTemp, Display, TEXT("Index %d is Room"), tileIndex);
			}

			//////////////////////
			//////////////////////
			///Spawner & Despawner set
			//////////////////////
			//////////////////////
			/////UE_LOG(LogTemp, Display, TEXT("Room %d is good"),roomToSpawn);
			if (size==minRoomSizeDefault) minRoomSize++;
			if (!success) break;
		}
		if (!success) break;
		if(i<startX+size-1) end++;
		else start++;
	}
	if(!success)
	{
		TileTypesTemp.Empty();
		TileTypesTemp.Append(TileTypesTempBackup);
	}
	else
	{
		for(int32 i = 0; i<RandomOdd(1,size-2);i++)
		{
			selIndex = TempRoom.WayTilesArray[RandomOdd(0,TempRoom.WayTilesArray.Num()-1)];
			TileTypesTemp[selIndex]=ETT_Block;
			TempRoom.WayTilesArray.Remove(selIndex);
		}
		switch(TempRoom.RoomType)
		{
		case ERT_SpawnRoom:
			for(int32 i = 0; i<2;i++)
			{
				selIndex = TempRoom.WayTilesArray[RandomOdd(0,TempRoom.WayTilesArray.Num()-1)];
				TileTypesTemp[selIndex]=ETT_Spawn;
				TempRoom.WayTilesArray.Remove(selIndex);
			}
			spawnCount++;
			spawned = true;
			break;
		case ERT_PortalRoom:
			selIndex = CoordToIndex(TempRoom.start + (TempRoom.size-1)*NeighsIndexes[3]);
			TileTypesTemp[selIndex]=ETT_Portal;
			TempRoom.WayTilesArray.Remove(selIndex);
			despawnCount++;
			spawned = true;
			break;
		case ERT_EnemyRoom:
			for (int32 i = 0; i < TempRoom.Enemies; i++)
			{
				selIndex = TempRoom.WayTilesArray[RandomOdd(0,TempRoom.WayTilesArray.Num()-1)];
				TileTypesTemp[selIndex] = ETT_EnemySpawn;
				TempRoom.WayTilesArray.Remove(selIndex);
			}
			break;
		case ERT_ChestRoom:
			selIndex = TempRoom.WayTilesArray[RandomOdd(0,TempRoom.WayTilesArray.Num()-1)];
			TileTypesTemp[selIndex]=ETT_Chest;
			TempRoom.WayTilesArray.Remove(selIndex);
			CurRoomType = ERT_KeyRoom;
			chestCount++;
			TileTypesTemp[TempRoom.cornerInd[(direction+3)%6]] = ETT_Door;
			break;
		case ERT_KeyRoom:
			selIndex = TempRoom.WayTilesArray[RandomOdd(0,TempRoom.WayTilesArray.Num()-1)];
			TileTypesTemp[selIndex]=ETT_Key;
			TempRoom.WayTilesArray.Remove(selIndex);
			for (int32 i = 0; i < TempRoom.Enemies; i++)
			{
				selIndex = TempRoom.WayTilesArray[RandomOdd(0,TempRoom.WayTilesArray.Num()-1)];
				TileTypesTemp[selIndex] = ETT_EnemySpawn;
				TempRoom.WayTilesArray.Remove(selIndex);
			}
			keyCount++;
			CurRoomType = ERT_Base;
			break;
		case ERT_ShopRoom:
			//selIndex = TempRoom.WayTilesArray[RandomOdd(0,TempRoom.WayTilesArray.Num()-1)];
			selIndex = CoordToIndex(IndexToCoord(TempRoom.cornerInd[direction])+NeighsIndexes[(direction+3)%6]*3);
			//selIndex = CoordToIndex(IndexToCoord(TempRoom.cornerInd[RandomOdd(0,TempRoom.cornerInd.Num()-1)])+
			//	NeighsIndexes[(direction+3)%6]*3);
			TileTypesTemp[selIndex]=ETT_Shop;
			TempRoom.WayTilesArray.Remove(selIndex);
			TileTypesTemp[TempRoom.cornerInd[(direction+3)%6]] = ETT_Door;
			shopCount++;
			break;
		default:
			break;
		}
		if (TempRoom.RoomType!=ERT_ChestRoom && TempRoom.RoomType!=ERT_ShopRoom) TileRooms.Add(TempRoom);
		direction = RandomOdd(0,TempRoom.cornerInd.Num()-1);
	}
	return success;
}

bool ATileMap::GenerateCorridor(int32 size)
{
	TileTypesTemp.Empty();
	TileTypesTemp.Append(TileTypesBackup);
	TileTypesTempBackup.Empty();
	TileTypesTempBackup.Append(TileTypesTemp);

	bool success = true;
	
	int32 startRoom = TileRooms.Num()-1;
	size = RandomOdd(minRoomSize,maxRoomSize);
	//sizeTemp = size;
	if (branching && RandStream.GetFraction()<branchChance && roomToSpawn<roomAmount-2) startRoom = RandomOdd(0,TileRooms.Num()-1);

	//UE_LOG(LogTemp, Warning, TEXT("RoomAmount %d startRoom %d"), TileRooms.Num()-1 ,  startRoom  );
	
	int32 dir = direction; //RandomOdd(0, TileRooms[startRoom].cornerInd.Num()-1);
	
	FVector2D startpoint = IndexToCoord(TileRooms[startRoom].cornerInd[dir]);
	
	TArray<int32> walls;
	for(int32 i = 1; i <= 2; i++)
	{
		walls.Add(CoordToIndex(startpoint+NeighsIndexes[(dir+2*i)%6]*2));
	}
	TArray<int32> floors;
	for(int32 i = 1; i <= 2; i++)
	{
		floors.Add(CoordToIndex(startpoint+NeighsIndexes[(dir+2*i)%6]));
	}
	
	int32 curIndex = CoordToIndex(startpoint);
	const int32 length = maxRoomSize*2-TileRooms[startRoom].size-size;
	//UE_LOG(LogTemp, Display, TEXT("I want to make corridor from room %d to direction %d of length %d and make new room of size %d"),startRoom, dir, length, size);
	sizeTemp = size;
	TileTypesTemp[curIndex]=ETT_Door;	
	for (int32 i = 1; i <= length+size*2+1; i++)
	{
		curIndex = CoordToIndex(startpoint+NeighsIndexes[dir]*i);
		for(int32 j = 0; j<=1; j++)
		{
			walls[j] = CoordToIndex(IndexToCoord(walls[j])+NeighsIndexes[dir]);
			floors[j] = CoordToIndex(IndexToCoord(floors[j])+NeighsIndexes[dir]);
		}
		if(TileTypesTempBackup[curIndex]!=ETT_None)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Corridor failed to generate because of collision at index %d"),curIndex);
			success = false;
			break;
		}
		else if (i<=length)
		{
			TileTypesTemp[curIndex]=ETT_Path;
		}
		if (i<=length+1) for(int32 idFloor : floors)
		{
			TileTypesTemp[idFloor]=ETT_Path;
		}
		if (i<=length+2) for(int32 idWall : walls)
		{
			TileTypesTemp[idWall]=ETT_Wall;
		}
	}
	//curIndex = CoordToIndex(startpoint+NeighsIndexes[dir]*length+size*2-1);
	if(!success)
	{
		TileTypesTemp.Empty();
		TileTypesTemp.Append(TileTypesTempBackup);
	}
	else
	{
		//UE_LOG(LogTemp, Display, TEXT("Corridor is good"));
		prevLocation = startpoint+(length+size)*NeighsIndexes[dir]+(size-1)*NeighsIndexes[0];
		//UE_LOG(LogTemp, Display, TEXT("Room is sized %d, and placed at %f %f"), size, prevLocation.X, prevLocation.Y);
	}
	return success;
}

FRotator ATileMap::CheckWallRotation(int32 Index)
{
	FRotator Rotation = FRotator().ZeroRotator;
	const FVector2D coord = IndexToCoord(Index);
	//UE_LOG(LogTemp, Display, TEXT("Index is %i Coord is %f %f"), Index, coord.X, coord.Y);
	//UE_LOG(LogTemp, Display, TEXT("Max %i"), std::size(NeighsIndexes));
	for (int32 i = 0; i < std::size(NeighsIndexes);i++)
	{
		//UE_LOG(LogTemp, Display, TEXT("Check %i"), i);
		const int32 CheckA = CoordToIndex(coord+NeighsIndexes[i]);
		//UE_LOG(LogTemp, Display, TEXT("Index is %i"), CheckA);
		if (TileTypes[CheckA]==ETT_Room)
        {
			//UE_LOG(LogTemp, Display, TEXT("SideA is %i"), i);
			if (TileTypes[CoordToIndex(coord+NeighsIndexes[(6+i+1)%6])]==ETT_Room)
			{
				//UE_LOG(LogTemp, Display, TEXT("SideB is %i"), (i+1)%6);
				Rotation = FRotator(0,(-((i)%6)*60),0);
				break;
			}
			if (TileTypes[CoordToIndex(coord+NeighsIndexes[(6+i-1)%6])]==ETT_Room)
			{
				//UE_LOG(LogTemp, Display, TEXT("SideB is %i"), (6+i-1)%6);
				Rotation = FRotator(0,(-((6+i-1)%6)*60),0);
				break;
			}
			Rotation = FRotator(0,i*-60,0);
			break;
		}
		if ( TileTypes[CheckA]==ETT_Path)
		{
			//UE_LOG(LogTemp, Display, TEXT("SideA is %i"), i);
			if (TileTypes[CoordToIndex(coord+NeighsIndexes[(6+i+1)%6])]==ETT_Path )
			{
				//UE_LOG(LogTemp, Display, TEXT("SideB is %i"), (i+1)%6);
				Rotation = FRotator(0,(-((i)%6)*60),0);
				break;
			}
			if (TileTypes[CoordToIndex(coord+NeighsIndexes[(6+i-1)%6])]==ETT_Path)
			{
				//UE_LOG(LogTemp, Display, TEXT("SideB is %i"), (6+i-1)%6);
				Rotation = FRotator(0,(-((6+i-1)%6)*60),0);
				break;
			}
			Rotation = FRotator(0,i*-60,0);
			break;
		}
	}
	return Rotation;
}

int32 ATileMap::RandomOdd(int32 Min, int32 Max)
{
	int32 result = RandStream.FRandRange(Min,Max);
	//if (result%2==0) result++;
	return result;
}

void ATileMap::FindOptionalCorridors()
{
	TempArraysSetup();
	for (int32 i = 0; i < TileRooms.Num()-2; i++)
	{
		FRoomStruct A = TileRooms[i];
		for (int32 j = i+1; j < TileRooms.Num()-1; j++)
		{			
			FRoomStruct B = TileRooms[j];

			FVector2D res = (B.start+(B.size-1))-(A.start+(A.size-1));
			
			//Directions 0 and 3 WORKS CORRECTLY
			if (((A.start+(A.size-1)).X - (A.start+(A.size-1)).Y == (B.start+(B.size-1)).X - (B.start+(B.size-1)).Y))
			{
				int32 len = res.Size();
				
				if (res < FVector2D().ZeroVector && TileTypes[A.cornerInd[0]]!=ETT_Door && RandStream.GetFraction()<optionalChance)
				{
					DoOptionalCorridors(A.cornerInd[0],B.cornerInd[3],0);
				}
				if (res > FVector2D().ZeroVector && TileTypes[A.cornerInd[3]]!=ETT_Door && RandStream.GetFraction()<optionalChance)
				{
					DoOptionalCorridors(A.cornerInd[3],B.cornerInd[0],3);
				}
			}
			//Directions 2 and 5 WORKS CORRECTLY
			else if ((A.start+(A.size-1)).X == (B.start+(B.size-1)).X)
			{
				int32 len = res.Size();

				if (res.Y > 0 && TileTypes[A.cornerInd[2]]!=ETT_Door && RandStream.GetFraction()<optionalChance)
				{
					DoOptionalCorridors(A.cornerInd[2],B.cornerInd[5],2);
				}
				if (res.Y < 0 && TileTypes[A.cornerInd[5]]!=ETT_Door && RandStream.GetFraction()<optionalChance)
				{
					DoOptionalCorridors(A.cornerInd[5],B.cornerInd[2],5);
				}
			}
			//Directions 1 and 4 WORKS CORRECTLY
			else if ((A.start+(A.size-1)).Y == (B.start+(B.size-1)).Y)
			{
				int32 len = res.Size();

				if (res.X < 0 && TileTypes[A.cornerInd[1]]!=ETT_Door && RandStream.GetFraction()<optionalChance)
				{
					DoOptionalCorridors(A.cornerInd[1],B.cornerInd[4],1);
				}
				if (res.X > 0 && TileTypes[A.cornerInd[4]]!=ETT_Door && RandStream.GetFraction()<optionalChance)
				{
					DoOptionalCorridors(A.cornerInd[4],B.cornerInd[1],4);
				}
			}
		}
	}
}

bool ATileMap::CheckSpawnDespawn()
{
	bool allSet = false;
	//UE_LOG(LogTemp, Warning, TEXT("Spawns places: %d, despawns placed %d"), spawnCount, despawnCount);
	if (spawnCount>=spawnAmount&&despawnCount>=despawnAmount) allSet=true;
	spawnCount=0;
	despawnCount=0;
	return allSet;
}

TArray<TEnumAsByte<ETileType>> ATileMap::GetNeighs(int32 index)
{
	FVector2D start = IndexToCoord(index);
	TArray<TEnumAsByte<ETileType>> NeighsArray;
	for (FVector2D dir : NeighsIndexes)
	{
		NeighsArray.Add(TileTypes[CoordToIndex(start+dir)]);
	}
	return NeighsArray;
}

FVector2D ATileMap::IndexToCoord(int32 index)
{
	return FVector2D(index/worldSize, index%worldSize);
}

int32 ATileMap::CoordToIndex(FVector2D coord)
{
	return (coord.X*worldSize+coord.Y);
}

//WARNING

void ATileMap::RoomCorCycle()
{
	bool tempgood=true;
	prevLocation = FVector2D(worldSize/2);
	for (int32 i = 0; i< triesToPlaceARoom;i++)
	{
		spawnCount = 0;
		despawnCount = 0;
		shopCount = 0;
		keyCount = 0;
		chestCount = 0;
		roomToSpawn = 0;
		prevLocation = FVector2D(worldSize/2);
		chestAmount = RandomOdd(1,2);
		keyAmount = chestAmount;
		TileTypesTemp.Empty();
		TileRooms.Empty();
		TileTypesTemp.Append(TileTypesTempBackup);
		while (roomToSpawn<roomAmount)
		{
			/////////////////////////
			/////////////////////////
			//Room Generation
			/////////////////////////
			/////////////////////////
			for (int32 j = 0; j<triesToPlaceARoom;j++)
			{
				TEnumAsByte<ERoomTypes> Room = ERT_EnemyRoom;
				if (CurRoomType == ERT_Base)
				{
                    if (roomToSpawn < spawnAmount) Room = ERT_SpawnRoom;
                    else if (roomToSpawn == roomAmount-1 ) Room = ERT_PortalRoom;
                    else
                    {
                    	 if (RandStream.GetFraction() < 0.5)
                    	 {
	                    	 if (shopCount<shopAmount) Room = ERT_ShopRoom;
	                    	 else Room = ERT_EnemyRoom; 
                    	 }
                    	else
                    	{
                    		if (chestCount<chestAmount) Room = ERT_ChestRoom;
                    		else Room = ERT_EnemyRoom; 
                    	}
                    }
				}
				else Room = CurRoomType;
				tempgood=GenerateRoom(roomToSpawn, sizeTemp, Room);
				if (tempgood) break;
			}
			if (tempgood)
			{
				TileTypesTempBackup.Empty();
				TileTypesTempBackup.Append(TileTypesTemp);
				TileTypesBackup.Empty();
				TileTypesBackup.Append(TileTypesTempBackup);
			}
			else
			{
				TileTypesTemp.Empty();
				TileTypesTemp.Append(TileTypesTempBackup);
				break;
			}
			//////////////////////
			//////////////////////
			//Corridor Generation
			//////////////////////
			//////////////////////
			for (int32 j = 0; j<triesToPlaceARoom;j++)
			{
				if (roomToSpawn<roomAmount-1)
				{
					tempgood=GenerateCorridor(RandomOdd(minRoomSize, maxRoomSize));
				}
				if (tempgood) break;
			}
			if (tempgood)
			{
				TileTypesTempBackup.Empty();
				TileTypesTempBackup.Append(TileTypesTemp);
				TileTypesBackup.Empty();
				TileTypesBackup.Append(TileTypesTempBackup);
			}
			else
			{
				TileTypesTemp.Empty();
				TileTypesTemp.Append(TileTypesTempBackup);
				break;
			}
			//Good? Next room generation
			roomToSpawn++;
		}
		if(CheckSpawnDespawn())
		{
			TileTypes = TileTypesBackup;
			break;
		}
		//Else
		seed = 0;
		//TempArraysSetup();
		GenerateAllIndexes();
		RandStreamGen();
		UE_LOG(LogTemp,Error, TEXT("Trying to generate another map with seed %d"), seed);
		
	}
}

void ATileMap::FinishRoomCorners()
{
	for (FRoomStruct Room : TileRooms)
	{
		for (int32 i = 0; i < Room.cornerInd.Num();i++)
		{
			int32 Ind_To_Check=CoordToIndex(IndexToCoord(Room.cornerInd[i])+NeighsIndexes[i]);
			if (TileTypes[Ind_To_Check]==ETT_Path) TileTypes[Room.cornerInd[i]]=ETT_Door;
		}
	}
}

void ATileMap::DoOptionalCorridors(int32 start, int32 end, int32 dir)
{
	TArray<int32> walls;
	for(int32 i = 1; i <= 2; i++)
	{
		walls.Add(CoordToIndex(IndexToCoord(start)+NeighsIndexes[(dir+2*i)%6]));
	}
	int32 length = 0;
	const FVector2D A = IndexToCoord(start);
	const FVector2D B = IndexToCoord(end);
	
	if ((dir % 3) == 0 ) length = abs((B.X-A.X));
	else if ((dir % 3) == 1 ) length = abs (B.X-A.X);
	else if ((dir % 3) == 2 ) length = abs (B.Y-A.Y);

	//UE_LOG(LogTemp,Display,TEXT("Distance is %i and direction is %i"), length, dir);
	if (length < maxRoomSize+1)
	{
		for (int32 i = 1; i <= length; i++)
        	{
        		int32 curIndex = CoordToIndex(A+NeighsIndexes[dir]*i);
        		for(int32 j = 0; j<=1; j++) walls[j] = CoordToIndex(IndexToCoord(walls[j])+NeighsIndexes[dir]);
        		if (i<=length)
        		{
        			TileTypesTemp[curIndex]=ETT_Path;
        		}
        		if (i<=length+1) for(int32 idWall : walls) TileTypesTemp[idWall]=ETT_Wall;
        	}
        	TileTypes = TileTypesTemp;
	}
}


// Called when the game starts or when spawned
void ATileMap::BeginPlay()
{
	Super::BeginPlay();
	DunGenMain();
	
	AGameMaster* GM = Cast<AGameMaster>(UGameplayStatics::GetPlayerCharacter(this,0));
	if(GM)
	{
	GM->Map = this;
	GetWorldTimerManager().SetTimer(TimerHandle, GM , &AGameMaster::SetNextChar, 2.0f);
		UE_LOG(LogTemp, Display, TEXT("Found Map"));
	}

}

