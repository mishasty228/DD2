// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "TilesStruct.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "GameFramework/Actor.h"
#include "TileBase.generated.h"

class ACharBase;
class ATileMap;
struct FCharDataStruct;

UCLASS()
class DD2_API ATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileBase();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTilesStruct TilesStruct = FTilesStruct();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	USphereComponent* Sphere;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
	USphereComponent* SphereToCheckNeighs;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Components")
	USceneComponent* Scene;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Tiles")
	ACharBase* CharacterOnTile;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Tiles")
	TArray<ATileBase*> Neighs;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileData")
	TArray<TEnumAsByte<ETileType>> TypeNeighs;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Tiles")
	TArray<ATileBase*> AvailableNeighs;

	UPROPERTY()
	UMaterialInstanceDynamic* MIDynamic;

	UPROPERTY()
	AActor* OnActor;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="TileCoordinates");
	FVector CubeCoordinates = FVector().ZeroVector;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TileCoordinates");
	FVector2D HexCoordinates = FVector2D().ZeroVector;

	UFUNCTION(BlueprintCallable)
	void OnStep( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							 UPrimitiveComponent* OtherComp,
							 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnSideSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                         UPrimitiveComponent* OtherComp,
	                         int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void CheckNeighs();

	UFUNCTION(BlueprintCallable)
	void CheckAvailableNeighs();

	
	
protected:
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetMatScalarParameter(FName Name, float Value);

	UFUNCTION(BlueprintCallable)
	void SetMatVectorParameter(FName Name, FLinearColor Value);
};
