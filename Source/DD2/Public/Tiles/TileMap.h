// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "TileBase.h"
#include "TileRoom.h"
#include "GameFramework/Actor.h"
#include "Math/RandomStream.h"
#include "TileMap.generated.h"

UCLASS()
class DD2_API ATileMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileMap();

	FActorSpawnParameters spawnParams = FActorSpawnParameters();
	
	UWorld* world = GetWorld();
	
	//Properties

	const FVector2D NeighsIndexes[6] = {FVector2D(-1,-1), FVector2D(-1,0), FVector2D(0,1),
		FVector2D(1,1), FVector2D(1,0), FVector2D(0,-1)};
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<ATileBase*> Tiles;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="MapData")
	FRandomStream RandStream;
	
	UPROPERTY()
	bool bUp = false;

	UPROPERTY()
	bool bRight = false;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<FRoomStruct> TileRooms;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
    TArray<TEnumAsByte<ETileType>> TileTypes;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<TEnumAsByte<ETileType>> TileTypesBackup;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<TEnumAsByte<ETileType>> TileTypesTemp;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<TEnumAsByte<ETileType>> TileTypesTempBackup;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<int32> PathStartIndexes;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 minRoomSize = 3;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 minRoomSizeDefault = 3;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 maxRoomSize = 5;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 seed = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector tileSpawnLocation;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 direction = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 sizeTemp = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	float offsetX = 86.6f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	float offsetY = 100.0f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector spawnLocation;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector2D prevLocation = FVector2D(1,1);

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector2D nextLocation = FVector2D(0,0);

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Spawn")
	FRotator rotator;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 worldSize=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 lastIndex=0;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 tileIndex=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 posX=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 posY=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 triesToPlaceARoom=100;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 skip=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 spawnAmount = 4;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 spawnCount = 4;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 despawnAmount = 1;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 despawnCount = 1;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 roomToSpawn=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 roomAmount=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	bool branching=false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	float branchChance=0.2f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileBase;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileSpawner;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileTypes")
	TSubclassOf<class ATileBase> TileDespawner;

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
	bool GenerateRoom(int32 roomnum, int32 size=0);

	UFUNCTION(BlueprintCallable)
	bool CheckSpawnDespawn();

	UFUNCTION(BlueprintCallable)
	int32 RandomOdd(int32 Min, int32 Max);

	UFUNCTION(BlueprintCallable)
	void FindOptionalCorridors();
	
	UFUNCTION(BlueprintCallable)
	bool GenerateCorridor(int32 size);

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
		
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
