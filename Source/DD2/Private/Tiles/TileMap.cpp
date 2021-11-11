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
	//WallsAndPathStarts();
	SpawnEveryIndex();
}

void ATileMap::SpawnEveryIndex()
{
	for (int32 i = 0; i < worldSize; i++)
	{
		posX = i;
		for (int32 j = 0; j < worldSize; j++)
		{
			posY = j;
			if(TileToSpawn&& (TileTypes[i*worldSize+j]!=ETT_None && TileTypes[i*worldSize+j]!=ETT_Last))
			{
				spawnLocation = this->GetActorLocation();
				spawnLocation+=FVector(offsetX*i,offsetY*j*2-offsetY*i,0);
				ATileBase* CurTile = GetWorld()->SpawnActor<ATileBase>(TileToSpawn,
				spawnLocation, rotator,	FActorSpawnParameters());
				CurTile->TilesStruct.r=i;
				CurTile->TilesStruct.q=j;
				CurTile->TilesStruct.Available = false;
				CurTile->TilesStruct.TileType = TileTypes[i*worldSize+j];
				Tiles.Add(CurTile);
				CurTile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld,
				true));
			}
		}
	}
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

void ATileMap::AllRoomsSetup()
{
	TempArraysSetup();
	for (int32 i = 0; i<roomAmount;i++)
	{
		for (int32 j = 0; j<triesToPlaceARoom;j++)
		{
			if (GenerateRoom(i)) break;
		}
	}
	if(!CheckSpawnDespawn()) AllRoomsSetup();
	else TileTypes = TileTypesBackup;
}

void ATileMap::WallsAndPathStarts()
{
	for(int32 i = 0; i < worldSize;i++)
	{
		for (int32 j = 0; j < worldSize; j++)
		{
			if (TileTypes[i*worldSize+j]==ETT_None)
			{
				if(i%2==1 && j%2==1)
				{
					TileTypes[i*worldSize+j]=ETT_Wall;
				}
				else if(i%2==0 && j%2==0)
				{
					TileTypes[i*worldSize+j]=ETT_PathStart;
					PathStartIndexes.Add(i*worldSize+j);
				}
			}
		}
	}
	
}

////////////////////////////////////////////////////
////////////////////GENERATES ROOM//////////////////
////////////////////////////////////////////////////

bool ATileMap::GenerateRoom(int32 roomnum, int32 size)
{
	
	TileTypesTemp.Empty();
	TileTypesTemp.Append(TileTypesBackup);
	TileTypesTempBackup.Empty();
	TileTypesTempBackup.Append(TileTypesTemp);

	bool success = true;

	TArray <int32> cornersTemp;

	if (size==0) size = RandomOdd(minRoomSize,maxRoomSize);
	
	int32 startX = prevLocation.X; //RandomOdd(1, worldSize-(size*2-1)-1);
	int32 startY = prevLocation.Y; //RandomOdd(1, worldSize-(size*2-1)-1);
	bool up = true;
	int32 start = startY;
	int32 end = startY+size;

	UE_LOG(LogTemp, Display, TEXT("ROOM is %d"), roomToSpawn);
	UE_LOG(LogTemp, Display, TEXT("SideSize is %d"), size);
	UE_LOG(LogTemp, Display, TEXT("StartX is %d"), startX);
	UE_LOG(LogTemp, Display, TEXT("StartY is %d"), startY);
	
	nextLocation = FVector2D(startX,startY);
	
	if (roomnum==0)
	{
		startX=prevLocation.X-size;
		startY=prevLocation.Y-size;
		start=prevLocation.Y-size;
		end=prevLocation.Y;
	}
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
			if (TileTypesTempBackup[tileIndex]!=ETT_None/*&&TileTypesTempBackup[tileIndex]!=ETT_Wall*/)
			{
				UE_LOG(LogTemp, Warning, TEXT("Room failed to generate because of collision at index %d"),
		tileIndex);
				success=false;
				//UE_LOG(LogTemp, Display, TEXT("Index %d is colliding"), tileIndex);
				break;
			}
			if((j==start||j==end-1)||(i==startX||i==startX+size*2-2))
			{
				TileTypesTemp[tileIndex]=ETT_Wall;
				//UE_LOG(LogTemp, Display, TEXT("Index %d is Wall"), tileIndex);
			}
			else if((j>start||j<end-1)||(i>startX||i<startX+size*2-2))
			{
				TileTypesTemp[tileIndex]=ETT_Room;
				//UE_LOG(LogTemp, Display, TEXT("Index %d is Room"), tileIndex);
			}

			//CornersOfRoomSetup
			/*if ((i==startX||i==startX+size*2-2||i==startX+size)&&(j==start||j==end-1))
			{
				cornersTemp.Add(CoordToIndex(FVector2D(i,j)));
			}*/
			
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
		UE_LOG(LogTemp, Display, TEXT("Room %d is good"),roomToSpawn);
		if (size==minRoomSizeDefault) minRoomSize++;
		/*TileTypesTempBackup.Empty();
		TileTypesTempBackup.Append(TileTypesTemp);
		TileTypesBackup.Empty();
		TileTypesBackup.Append(TileTypesTempBackup);*/
		TileRooms.Add(FRoomStruct());
		TileRooms[roomnum].cornerInd.Append(cornersTemp);
		TileRooms[roomnum].size = size;
		TileRooms[roomnum].start = FVector2D(nextLocation);
		//prevLocation = nextLocation;
		//if (roomnum>0) TryCreateCorridor(roomnum);
		direction = RandomOdd(0,5);
		
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
	//if (result%2==0) result++;
	return result;
}

void ATileMap::TryCreateCorridor(int32 cornum)
{
	int32 roomStart=0;
	int32 roomEnd=0;

	int32 AX =0;
	int32 AY =0;
	int32 AiX =0;
	int32 AiY =0;
	
	int32 BX =0;
	int32 BiX =0;
	int32 BY =0;
	int32 BiY =0;
	
	UE_LOG(LogTemp, Display, TEXT("I am %d corridor"),	cornum )
	bool done = false;
	if (branching)
	{
		if (TileRooms.Num()>1 && RandStream.FRand()<branchChance)
		{
			roomEnd=TileRooms.Num()-1;
			roomStart = RandStream.RandRange(0,TileRooms.Num()-2);
			UE_LOG(LogTemp, Display, TEXT("I want to branch and make corridor between %d and %d room"),	roomStart, roomEnd );
			done = true;
		}
	}
	if (!done)
	{
		if (TileRooms.Num()>1)
		{
			roomEnd=TileRooms.Num()-1;
			roomStart = roomEnd-1;
			UE_LOG(LogTemp, Display, TEXT("I want to make corridor between %d and %d room"),roomStart, roomEnd );
		}
	}

	AX = TileRooms[roomStart].start.X;
	AY = TileRooms[roomStart].start.Y;
	AiX = TileRooms[roomStart].start.X+TileRooms[roomStart].size*2-1;
	AiY = TileRooms[roomStart].start.Y+TileRooms[roomStart].size*2-1;

	BX = TileRooms[roomEnd].start.X;
	BY = TileRooms[roomEnd].start.Y;
	BiX = TileRooms[roomEnd].start.X+TileRooms[roomEnd].size*2-1;
	BiY = TileRooms[roomEnd].start.Y+TileRooms[roomEnd].size*2-1;

	if (AreRoomsParallelOnX(AX,AiX,BX,BiX))
	{
		if(IsRoomBUp(AX,BX))
		{
			UE_LOG(LogTemp, Display, TEXT("Room %d is lower than room %d"),roomStart, roomEnd );
			direction = 2;
		}
		else UE_LOG(LogTemp, Display, TEXT("Room %d is upper than room %d"),roomStart, roomEnd );
		direction = 4;
	}
	else if (AreRoomsParallelOnY(AY,AiY,BY,BiY))
	{
		if(IsRoomBRight(AY,BY))
		{
			UE_LOG(LogTemp, Display, TEXT("Room %d is right to room %d"),roomStart, roomEnd );
			direction = 2;
		}
		else UE_LOG(LogTemp, Display, TEXT("Room %d is left to room %d"),roomStart, roomEnd );
		direction = 5;
	}
	else if (IsRoomBUp(AX,BX)&&IsRoomBRight(AY,BY))
	{
		UE_LOG(LogTemp, Display, TEXT("Room %d is DOWN-RIGHT to room %d"),roomStart, roomEnd );
		direction = 3;
	}
	else if (!IsRoomBUp(AX,BX)&&!IsRoomBRight(AY,BY))
	{
		UE_LOG(LogTemp, Display, TEXT("Room %d is UP-LEFT to room %d"),roomStart, roomEnd );
		direction = 0;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Rooms %d and %d are not parallel"),roomStart, roomEnd );
		if (cornum>1) TryCreateCorridor(cornum);
	}
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
	
	if (branching && RandStream.GetFraction()<branchChance) startRoom = RandomOdd(0,roomToSpawn);
	
	int32 dir = RandomOdd(0, 5);
	
	FVector2D startpoint = IndexToCoord(TileRooms[startRoom].cornerInd[dir]);
	
	TArray<int32> walls;
	for(int32 i = 1; i <= 2; i++)
	{
		walls.Add(CoordToIndex(startpoint+NeighsIndexes[(dir+2*i)%6]));
	}

	//for(int32 j = 0; j<=1; j++) walls[j] = CoordToIndex(IndexToCoord(walls[j])+NeighsIndexes[dir]);
	
	int32 curIndex = CoordToIndex(startpoint);
	int32 length = RandomOdd(minRoomSize,maxRoomSize);
	UE_LOG(LogTemp, Display, TEXT("I want to make corridor from room %d to direction %d of length %d and make new room of size %d"),
		startRoom, dir, length, size);
	sizeTemp = size;
	TileTypesTemp[curIndex]=ETT_Door;	
	for (int32 i = 1; i <= length+size*2+1; i++)
	{
		curIndex = CoordToIndex(startpoint+NeighsIndexes[dir]*i);
		for(int32 j = 0; j<=1; j++) walls[j] = CoordToIndex(IndexToCoord(walls[j])+NeighsIndexes[dir]);
		if(TileTypesTempBackup[curIndex]!=ETT_None)
		{
			UE_LOG(LogTemp, Warning, TEXT("Corridor failed to generate because of collision at index %d"),
		curIndex);
			success = false;
			break;
		}
		else if (i<=length)
		{
			TileTypesTemp[curIndex]=ETT_Path;
		}
		if (i<=length+1) for(int32 idWall : walls) TileTypesTemp[idWall]=ETT_Wall;
	}
	//curIndex = CoordToIndex(startpoint+NeighsIndexes[dir]*length+size*2-1);
	if(!success)
	{
		TileTypesTemp.Empty();
		TileTypesTemp.Append(TileTypesTempBackup);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Corridor is good"));
		
		prevLocation = startpoint+(length+size)*NeighsIndexes[dir]+(size-1)*NeighsIndexes[0];
		UE_LOG(LogTemp, Display, TEXT("Room is sized %d, and placed at %f %f"), size, prevLocation.X, prevLocation.Y);
	}
	return success;
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
	for (; roomToSpawn<roomAmount;)
	{
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
		for (int32 j = 0; j<triesToPlaceARoom;j++)
		{
			if (roomToSpawn<roomAmount-1)
			{
				tempgood=GenerateCorridor(RandomOdd(minRoomSize, maxRoomSize));
			}
			if (tempgood) break;
		}
		/*if (roomToSpawn<roomAmount-1)
		{
			for (int32 j = 0; j<triesToPlaceARoom;j++)
			{
				tempgood=GenerateCorridor(RandomOdd(minRoomSize, maxRoomSize));
				if (tempgood) break;
			}
		}*/
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
		roomToSpawn++;
	}
	if(!CheckSpawnDespawn()) AllRoomsSetup();
	else TileTypes = TileTypesBackup;
}

void ATileMap::FinishRoomCorners()
{
	for (FRoomStruct Room : TileRooms)
	{
		for (int32 i = 0; i < Room.cornerInd.Num();i++)
		{
			int32 ind_to_check=CoordToIndex(IndexToCoord(Room.cornerInd[i])+NeighsIndexes[i]);
			if (TileTypes[ind_to_check]==ETT_Path) TileTypes[Room.cornerInd[i]]=ETT_Door;
		}
	}
}

bool ATileMap::IsRoomBUp(int32 ax, int32 bx)
{
	return (bx>ax);
}

bool ATileMap::IsRoomBRight(int32 ay, int32 by)
{
	return (by>ay);
}

bool ATileMap::AreRoomsParallelOnX(int32 ax, int32 aix, int32 bx, int32 bix)
{
	return ((FMath::Max(ax,bx))<=(FMath::Min(aix,bix)));
}

bool ATileMap::AreRoomsParallelOnY(int32 ay, int32 aiy, int32 by, int32 biy)
{
	return ((FMath::Max(ay,by))<=(FMath::Min(aiy,biy)));
}

// Called when the game starts or when spawned
void ATileMap::BeginPlay()
{
	Super::BeginPlay();
	RandStreamGen();
	minRoomSizeDefault = minRoomSize;
	prevLocation = FVector2D(worldSize/2);
	//DunGenMain();
	GenerateAllIndexes();
	TempArraysSetup();
	RoomCorCycle();
	FinishRoomCorners();
	SpawnEveryIndex();
	/*GenerateRoom(roomToSpawn);
	TileTypes = TileTypesBackup;*/
	
}

// Called every frame
void ATileMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

