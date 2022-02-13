// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "MapTypes.h"
#include "TileBase.h"
#include "TileRoom.h"
#include "GameFramework/Actor.h"
#include "Math/RandomStream.h"
#include "Kismet/GameplayStatics.h"
#include "TileMap.generated.h"

class AGameMaster;

UCLASS()
class DD2_API ATileMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileMap();

	FActorSpawnParameters spawnParams = FActorSpawnParameters();
	
	UWorld* world = GetWorld();

	FTimerHandle TimerHandle;
	
	//Properties

	const FVector2D NeighsIndexes[6] = {FVector2D(-1,-1), FVector2D(-1,0), FVector2D(0,1),
		FVector2D(1,1), FVector2D(1,0), FVector2D(0,-1)};
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<ATileBase*> Tiles;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="MapData")
	FRandomStream RandStream;
	
	//UPROPERTY()
	//bool bUp = false;

	//UPROPERTY()
	//bool bRight = false;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<FRoomStruct> TileRooms;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
    TArray<TEnumAsByte<ETileType>> TileTypes;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<TEnumAsByte<ETileType>> TileTypesBackup;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<TEnumAsByte<ETileType>> TileTypesTemp;
	
	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<TEnumAsByte<ETileType>> TileTypesTempBackup;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	TEnumAsByte<EMapTypes> MapType = EMT_Base;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 minRoomSize = 3;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 minRoomSizeDefault = 3;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 maxRoomSize = 5;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 seed = 0;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector tileSpawnLocation;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 direction = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 sizeTemp = 0;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	float offsetX = 150.f;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	float offsetY = 86.6f;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector spawnLocation;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector2D prevLocation = FVector2D(1,1);

	//UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector2D nextLocation = FVector2D(0,0);

	//UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Spawn")
	FRotator rotator;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 worldSize=0;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 lastIndex=0;
	
	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 tileIndex=0;
	
	int32 selIndex=0;

    TEnumAsByte<ERoomTypes> CurRoomType = ERT_Base;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 posX=0;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 posY=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 triesToPlaceARoom=100;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	//int32 skip=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 spawnAmount = 4;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 spawnCount = 4;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 despawnAmount = 1;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 despawnCount = 1;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 chestAmount = 0;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 chestCount = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 keyAmount = 0;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 keyCount = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 shopAmount = 1;

	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 shopCount = 0;
	
	//UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 roomToSpawn=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 roomAmount=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 minEnemies=2;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 maxEnemies=4;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	bool branching=false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	float branchChance=0.2f;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	float optionalChance=0.2f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileBase;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileSpawner;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileDespawner;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileEnemy;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileShop;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileChest;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileDoor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileWall;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileBlock;

	//Functions

	UFUNCTION(BlueprintCallable)
	void DunGenMain();

	UFUNCTION(BlueprintCallable)
	void SpawnEveryIndex();

	UFUNCTION(BlueprintCallable)
	void GenerateAllIndexes();

	UFUNCTION(BlueprintCallable)
	void TempArraysSetup();

	UFUNCTION(BlueprintCallable)
	void RandStreamGen();
	
	UFUNCTION(BlueprintCallable)
	bool GenerateRoom(int32 roomnum, int32 size=0, TEnumAsByte<ERoomTypes> RoomType = ERT_EnemyRoom);

	UFUNCTION(BlueprintCallable)
	bool CheckSpawnDespawn();

	UFUNCTION(BlueprintCallable)
	int32 RandomOdd(int32 Min, int32 Max);

	UFUNCTION(BlueprintCallable)
	void FindOptionalCorridors();
	
	UFUNCTION(BlueprintCallable)
	bool GenerateCorridor(int32 size);

	UFUNCTION(BlueprintCallable)
	FRotator CheckWallRotation(int32 Index);

	//Tile Functions

	UFUNCTION(BlueprintCallable)
	TArray<TEnumAsByte<ETileType>> GetNeighs(int32 index);

	UFUNCTION(BlueprintCallable)
	FVector2D IndexToCoord(int32 index);

	UFUNCTION(BlueprintCallable)
	int32 CoordToIndex(FVector2D coord);

	UFUNCTION(BlueprintCallable)
	void RoomCorCycle();

	UFUNCTION(BlueprintCallable)
	void FinishRoomCorners();

	UFUNCTION(BlueprintCallable)
	void DoOptionalCorridors(int32 start, int32 end, int32 dir);

	UFUNCTION(BlueprintCallable)
    ATileBase* FindTileByIndex(int32 index);

    UFUNCTION(BlueprintCallable)
    TArray<ATileBase*> FindTilesInRange(int32 index, int32 range);

	UFUNCTION(BlueprintCallable)
    TArray<ATileBase*> FindTilesReachable(int32 index, int32 range);

	TArray<int32> FindPathRoute(int32 A, int32 B);
	
	UFUNCTION()
	int32 GetDistance(int32 A, int32 B);

	int32 GetTDistance(int32 B);

	int32 GetFDistance(int32 A, int32 B, int32 C);

	TArray<int32> SortFG(TArray<int32> indexes);
	
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
