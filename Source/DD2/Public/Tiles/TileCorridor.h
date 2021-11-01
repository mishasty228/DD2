// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TileBase.h"
//#include "TileRoom.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "TileCorridor.generated.h"

UCLASS()
class DD2_API ATileCorridor : public AActor
{
	GENERATED_BODY()
	
public:

	FActorSpawnParameters spawnParams = FActorSpawnParameters();
	
	UWorld* world = GetWorld();
	
	// Sets default values for this actor's properties
	ATileCorridor();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	USphereComponent* SphereStart;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	USphereComponent* SphereEnd;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="RoomParams")
	float offsetX = 86.6f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="RoomParams")
	float offsetY = 150.0f;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RoomParams")
	int32 sideDir = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Spawn")
	FRotator rotator;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RoomParams")
	int32 corridorMinLength = 1;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RoomParams")
	int32 corridorMaxLength = 2;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="RoomParams")
	int32 len = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileData")
	TSubclassOf<class ATileBase> TileSpawn;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<FVector2D> coordsToSpawn;
	
	FVector2D offsetDirs[6] = {FVector2D(-offsetY,-offsetX), FVector2D(-offsetY,offsetX),
		FVector2D(0,-2*offsetX), FVector2D(0,2*offsetX),
		FVector2D(offsetY,-offsetX), FVector2D(offsetY,offsetX)};

	UFUNCTION(BlueprintCallable)
	void GenerateCorridor(int32 length);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
