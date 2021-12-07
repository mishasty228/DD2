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
	//minRoomSizeDefault = minRoomSize;
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
			switch (TileTypes[i*worldSize+j])
			{
			case ETT_Room:
				if(TileBase)
				{
					spawnLocation = this->GetActorLocation();
					spawnLocation+=FVector(offsetX*i,offsetY*j*2-offsetY*i,0);
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileBase,
					spawnLocation, rotator,	FActorSpawnParameters());
					CurTile->TilesStruct.r=i;
					CurTile->TilesStruct.q=j;
					CurTile->TilesStruct.s=i-j;
					CurTile->TilesStruct.Available = false;
					CurTile->TilesStruct.TileType = TileTypes[i*worldSize+j];
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Path:
				if(TileBase)
				{
					spawnLocation = this->GetActorLocation();
					spawnLocation+=FVector(offsetX*i,offsetY*j*2-offsetY*i,0);
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileBase,
					spawnLocation, rotator,	FActorSpawnParameters());
					CurTile->TilesStruct.r=i;
					CurTile->TilesStruct.q=j;
					CurTile->TilesStruct.s=i-j;
					CurTile->TilesStruct.Available = false;
					CurTile->TilesStruct.TileType = TileTypes[i*worldSize+j];
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Door:
				if(TileBase)
				{
					spawnLocation = this->GetActorLocation();
					spawnLocation+=FVector(offsetX*i,offsetY*j*2-offsetY*i,0);
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileBase,
					spawnLocation, rotator,	FActorSpawnParameters());
					CurTile->TilesStruct.r=i;
					CurTile->TilesStruct.q=j;
					CurTile->TilesStruct.s=i-j;
					CurTile->TilesStruct.Available = false;
					CurTile->TilesStruct.TileType = TileTypes[i*worldSize+j];
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Wall:
				if(TileBase)
				{
					spawnLocation = this->GetActorLocation();
					spawnLocation+=FVector(offsetX*i,offsetY*j*2-offsetY*i,0);
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileBase,
					spawnLocation, rotator,	FActorSpawnParameters());
					CurTile->TilesStruct.r=i;
					CurTile->TilesStruct.q=j;
					CurTile->TilesStruct.s=i-j;
					CurTile->TilesStruct.Available = false;
					CurTile->TilesStruct.TileType = TileTypes[i*worldSize+j];
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Spawn:
				if(TileSpawner)
				{
					spawnLocation = this->GetActorLocation();
					spawnLocation+=FVector(offsetX*i,offsetY*j*2-offsetY*i,0);
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileSpawner,
					spawnLocation, rotator,	FActorSpawnParameters());
					CurTile->TilesStruct.r=i;
					CurTile->TilesStruct.q=j;
					CurTile->TilesStruct.s=i-j;
					CurTile->TilesStruct.Available = false;
					CurTile->TilesStruct.TileType = TileTypes[i*worldSize+j];
					Tiles.Add(CurTile);
					CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
					true));
				}
				break;
			case ETT_Portal:
				if(TileBase)
				{
					spawnLocation = this->GetActorLocation();
					spawnLocation+=FVector(offsetX*i,offsetY*j*2-offsetY*i,0);
					ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileBase,
					spawnLocation, rotator,	FActorSpawnParameters());
					CurTile->TilesStruct.r=i;
					CurTile->TilesStruct.q=j;
					CurTile->TilesStruct.s=i-j;
					CurTile->TilesStruct.Available = false;
					CurTile->TilesStruct.TileType = TileTypes[i*worldSize+j];
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

/**
 * @brief Generates room at certain location
 * @param roomnum Current number of rooms generated
 * @param size Size of one side of a room, so length or width of a room will be 2size-1
 * @return true if not collided with any other room
 */
bool ATileMap::GenerateRoom(int32 roomnum, int32 size)
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
	bool up = true;

	
	//UE_LOG(LogTemp, Display, TEXT("ROOM is %d"), roomToSpawn);
	
	if (roomnum==0)
	{
		startX=prevLocation.X-size+1;
		startY=prevLocation.Y-size+1;
	}

	

	int32 start = startY;
	int32 end = startY+size;
	
	nextLocation = FVector2D(startX,startY);
	
	//CornersOfRoomSetup
	for (FVector2D dir : NeighsIndexes)
	{
		cornersTemp.Add(CoordToIndex(FVector2D(startX+size-1, startY+size-1)+dir*(size-1)));
	}
	
	for (int32 i = startX; i < (startX+(size*2-1)); i++)
	{
		for(int32 j = start; j < end; j++)
		{
			tileIndex = worldSize*i+j;
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
			else if((j>start&&j<end-1)||(i>startX&&i<startX+size*2-2))
			{
				TileTypesTemp[tileIndex]=ETT_Room;
				//UE_LOG(LogTemp, Display, TEXT("Index %d is Room"), tileIndex);
			}

			//////////////////////
			//////////////////////
			///Spawner & Despawner set
			//////////////////////
			//////////////////////
			
			if (roomnum<roomAmount-despawnAmount&&RandStream.GetFraction()<0.5)
			{
				if((j>start+1&&j<end-2)&&(i>startX+1&&i<startX+size*2-3))
                {
					if (RandStream.GetFraction()<0.2&&!spawned&&spawnCount<spawnAmount)
					{
						TileTypesTemp[tileIndex]=ETT_Spawn;
						spawned = true;
						//UE_LOG(LogTemp, Warning, TEXT("Spawner placed at %d, %d"), i-startX, j-start);
					}
                }
			}
			else if (roomnum>=roomAmount-despawnAmount)
			{
				if((j==end-size)&&(i==startX+size-1))
				{
					if (RandStream.GetFraction()<0.9&&!spawned&&despawnCount<despawnAmount)
					{
						TileTypesTemp[tileIndex]=ETT_Portal;
						spawned = true;
						//UE_LOG(LogTemp, Warning, TEXT("Despawner placed at  %d, %d"), i-startX, j-start);
					}
				}
			}
			
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
		//UE_LOG(LogTemp, Display, TEXT("Room %d is good"),roomToSpawn);
		if (size==minRoomSizeDefault) minRoomSize++;
		if (spawned)
		{
			if (roomnum<roomAmount-despawnAmount) spawnCount++;
			else despawnCount++;
		}
		TileRooms.Add(FRoomStruct());
		TileRooms[roomnum].cornerInd.Append(cornersTemp);
		TileRooms[roomnum].size = size;
		TileRooms[roomnum].start = FVector2D(nextLocation);
		direction = RandomOdd(0,5);
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
	
	int32 startRoom = roomToSpawn;
	size = RandomOdd(minRoomSize,maxRoomSize);
	
	if (branching && RandStream.GetFraction()<branchChance && roomToSpawn<roomAmount-2) startRoom = RandomOdd(0,roomToSpawn);
	
	int32 dir = RandomOdd(0, 5);
	
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
	//for(int32 j = 0; j<=1; j++) walls[j] = CoordToIndex(IndexToCoord(walls[j])+NeighsIndexes[dir]);
	
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
			//UE_LOG(LogTemp, Display, TEXT("Rooms %i and %i"), i, j);
			
			FRoomStruct B = TileRooms[j];

			FVector2D res = (B.start+(B.size-1))-(A.start+(A.size-1));
			//UE_LOG(LogTemp, Display, TEXT("Res vector is %f and %f "), res.X, res.Y);
			
			//Directions 0 and 3 WORKS CORRECTLY
			if (((A.start+(A.size-1)).X - (A.start+(A.size-1)).Y == (B.start+(B.size-1)).X - (B.start+(B.size-1)).Y))
			{
				//FVector2D res = (B.start+(B.size-1))-(A.start+(A.size-1));
				int32 len = res.Size();
				UE_LOG(LogTemp, Display, TEXT("XYDistance between rooms %i and %i is %i "), i, j , len);
				//UE_LOG(LogTemp, Display, TEXT("Res vector is %f and %f "), res.X, res.Y);
				
				//if (len<maxRoomSize*3)
				//{
				if (res < FVector2D().ZeroVector && TileTypes[A.cornerInd[0]]!=ETT_Door && RandStream.GetFraction()<optionalChance)
				{
					DoOptionalCorridors(A.cornerInd[0],B.cornerInd[3],0);
					/*UE_LOG(LogTemp, Display, TEXT("Room %i can be connected with Room %i at corner 0"), i, j);
					TileTypes[A.cornerInd[0]]= ETT_Door;
					TileTypes[B.cornerInd[3]]= ETT_Door;*/
				}
				if (res > FVector2D().ZeroVector && TileTypes[A.cornerInd[3]]!=ETT_Door && RandStream.GetFraction()<optionalChance)
				{
					DoOptionalCorridors(A.cornerInd[3],B.cornerInd[0],3);
					/*UE_LOG(LogTemp, Display, TEXT("Room %i can be connected with Room %i at corner 3"), i, j);
					TileTypes[B.cornerInd[0]]= ETT_Door;
					//TileTypes[A.cornerInd[3]]= ETT_Door;*/
				}
				//}
			}
			
			//Directions 2 and 5 WORKS CORRECTLY
			else if ((A.start+(A.size-1)).X == (B.start+(B.size-1)).X)
			{
				//FVector2D res = (B.start+(B.size-1))-(A.start+(A.size-1));
				int32 len = res.Size();
				UE_LOG(LogTemp, Display, TEXT("XDistance between rooms %i and %i is %i"), i, j , len);
				
				//if (len<maxRoomSize*3)
				//{
				if (res.Y > 0 && TileTypes[A.cornerInd[2]]!=ETT_Door && RandStream.GetFraction()<optionalChance)
				{
					DoOptionalCorridors(A.cornerInd[2],B.cornerInd[5],2);
					/*UE_LOG(LogTemp, Display, TEXT("Room %i can be connected with Room %i at corner 2"), i, j);
					TileTypes[A.cornerInd[2]]= ETT_Door;
					TileTypes[B.cornerInd[5]]= ETT_Door;*/
				}
				if (res.Y < 0 && TileTypes[A.cornerInd[5]]!=ETT_Door && RandStream.GetFraction()<optionalChance)
				{
					DoOptionalCorridors(A.cornerInd[5],B.cornerInd[2],5);
					/*UE_LOG(LogTemp, Display, TEXT("Room %i can be connected with Room %i at corner 5"), i, j);
					TileTypes[A.cornerInd[5]]= ETT_Door;
					TileTypes[B.cornerInd[2]]= ETT_Door;*/
				}
				//}
			}
			
			//Directions 1 and 4 WORKS CORRECTLY
			else if ((A.start+(A.size-1)).Y == (B.start+(B.size-1)).Y)
			{
				int32 len = res.Size();
				UE_LOG(LogTemp, Display, TEXT("YDistance between rooms %i and %i is %i"), i, j , len);
				//UE_LOG(LogTemp, Display, TEXT("Res vector is %f and %f "), res.X, res.Y);
				//if (len<maxRoomSize*3)
				//{
				if (res.X < 0 && TileTypes[A.cornerInd[1]]!=ETT_Door && RandStream.GetFraction()<optionalChance)
				{
					DoOptionalCorridors(A.cornerInd[1],B.cornerInd[4],1);
					/*UE_LOG(LogTemp, Display, TEXT("Room %i can be connected with Room %i at corner 1"), i, j);
					TileTypes[A.cornerInd[1]]= ETT_Door;
					TileTypes[B.cornerInd[4]]= ETT_Door;*/
				}
				if (res.X > 0 && TileTypes[A.cornerInd[4]]!=ETT_Door && RandStream.GetFraction()<optionalChance)
				{
					DoOptionalCorridors(A.cornerInd[4],B.cornerInd[1],4);
					/*UE_LOG(LogTemp, Display, TEXT("Room %i can be connected with Room %i at corner 4"), i, j);
					TileTypes[A.cornerInd[4]]= ETT_Door;
					TileTypes[B.cornerInd[1]]= ETT_Door;*/
				}
				//}
			}
		}
	}
}

bool ATileMap::CheckSpawnDespawn()
{
	bool allSet = true;
	UE_LOG(LogTemp, Warning, TEXT("Spawns places: %d, despawns placed %d"), spawnCount, despawnCount);
	if (spawnCount>=spawnAmount&&despawnCount>=despawnAmount) allSet=true;
	else allSet=false;
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

void ATileMap::RoomCorCycle()
{
	bool tempgood=true;
	for (int32 i = 0; i< triesToPlaceARoom;i++)
	{
		spawnCount = 0;
		despawnCount = 0;
		roomToSpawn = 0;
		TileTypesTemp.Empty();
		TileRooms.Empty();
		TileTypesTemp.Append(TileTypesTempBackup);
		for (; roomToSpawn<roomAmount;)
		{
			/////////////////////////
			/////////////////////////
			//Room Generation
			/////////////////////////
			/////////////////////////
			for (int32 j = 0; j<triesToPlaceARoom;j++)
			{
				tempgood=GenerateRoom(roomToSpawn,sizeTemp);
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
		else
		{
			seed = 0;
			TempArraysSetup();
			RandStreamGen();
			UE_LOG(LogTemp,Error, TEXT("Trying to generate another map with seed %d"), seed);
			//GenerateAllIndexes();
		}
		
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

	UE_LOG(LogTemp,Display,TEXT("Distance is %i and direction is %i"), length, dir);
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
}

// Called every frame
void ATileMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

