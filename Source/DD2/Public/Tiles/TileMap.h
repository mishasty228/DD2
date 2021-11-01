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

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<ATileBase*> TilesBackup;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<ATileBase*> TilesTemp;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<ATileBase*> TilesTempBackup;	
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<ATileRoom*> TileRooms;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
    TArray<TEnumAsByte<ETileType>> TileTypes;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<int32> PathStartIndexes;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 minRoomSize = 3;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 maxRoomSize = 5;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 seed = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector tileSpawnLocation;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float offsetX = 86.6f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float offsetY = 100.0f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector spawnLocation;

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
	int32 roomToSpawn=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="MapData")
	int32 roomAmount=0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileData")
	TSubclassOf<class ATileBase> TileToSpawn;

	//Functions

	UFUNCTION(BlueprintCallable)
	void DunGenMain();

	UFUNCTION(BlueprintCallable)
	void GenerateAllIndexes();

	UFUNCTION(BlueprintCallable)
	void TempArraysSetup();

	UFUNCTION(BlueprintCallable)
	void RandStreamGen();

	UFUNCTION(BlueprintCallable)
	void AllRoomsSetup();

	UFUNCTION(BlueprintCallable)
	void WallsAndPathStarts();

	UFUNCTION(BlueprintCallable)
	bool GenerateRoom();

	UFUNCTION(BlueprintCallable)
	bool CheckSpawnDespawn();

	UFUNCTION(BlueprintCallable)
	int32 RandomOdd(int32 Min, int32 Max);
	
	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
