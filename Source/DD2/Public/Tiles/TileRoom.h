// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "FRoomStruct.h"
#include "RoomTypes.h"
#include "TileBase.h"
#include "TileCorridor.h"
#include "TileRoom.generated.h"

/**
 * 
*/

UCLASS()

class DD2_API ATileRoom : public AActor
{

	GENERATED_BODY()
	
public:

	FActorSpawnParameters spawnParams = FActorSpawnParameters();
	
	UWorld* world = GetWorld();

	/////////////////////////////////////////
	//////////////PROPERTIES/////////////////
	/////////////////////////////////////////

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FRoomStruct RoomStruct = FRoomStruct();
	
	const FVector2D upHalfDirs[6] = {FVector2D(-1,-1), FVector2D(-1,0),FVector2D(0,-1),
		FVector2D(0,1),FVector2D(1,0),FVector2D(1,1)};

	const FVector2D midDirs[6] = {FVector2D(-1,-1), FVector2D(-1,0),FVector2D(0,-1),
		FVector2D(0,1),FVector2D(1,-1),FVector2D(1,0)};
	
	const FVector2D downHalfDirs[6] = {FVector2D(-1,0), FVector2D(-1,1),FVector2D(0,-1),
		FVector2D(0,1),FVector2D(1,-1),FVector2D(1,0)};

	FVector2D offsetDirs[6] = {FVector2D(-offsetY,-offsetX), FVector2D(-offsetY,offsetX),
		FVector2D(0,-2*offsetX), FVector2D(0,2*offsetX),
		FVector2D(offsetY,-offsetX), FVector2D(offsetY,offsetX)};

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<int32> cornerInd;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Spawn")
	FRotator rotator;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Spawn")
	FVector spawnLocation;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RoomParams")
	int32 sizeMin = 3;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RoomParams")
	int32 sizeMax = 5;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="RoomParams")
	int32 size=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="RoomParams")
	int32 currentRow=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="RoomParams")
	int32 doorsAmount=1;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="RoomParams")
	float offsetX = 86.6f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="RoomParams")
	float offsetY = 100.0f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="RoomParams")
	FVector currentOffset = FVector(0,0,0);

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="RoomParams")
	bool hasLake = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="RoomParams")
	bool hasKey = false;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="TileData")
	TArray<ATileBase*> TilesArray;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="RoomParams")
	TEnumAsByte<ERoomTypes> RoomType = ERT_Base;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileData")
	TSubclassOf<class ATileBase> TileToSpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class ATileCorridor> CorridorToSpawn;

	
	/////////////////////////////////////////
	//////////////FUNCTIONS//////////////////
	/////////////////////////////////////////
	
	UFUNCTION(BlueprintCallable)
	void GenerateRoom(int32 sideSize);
	
	UFUNCTION(BlueprintCallable)
	void GenerateRow(int32 rowLength);

	UFUNCTION(BlueprintCallable)
	void AllTilesCheckNeighs();

	UFUNCTION(BlueprintCallable)
	int32 CoordToIndex(int32 r, int32 q);

	UFUNCTION(BlueprintCallable)
	void SetTileNeighs(ATileBase* Tile);

	UFUNCTION(BlueprintCallable)
	void MakeDoorAtRandomCorner(int32 amount);
	
	ATileRoom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
