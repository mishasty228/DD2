// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TilesStruct.h"
#include "Char/CharBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "TileBase.generated.h"

UCLASS()
class DD2_API ATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileBase();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTilesStruct TilesStruct = FTilesStruct();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USceneComponent* Scene;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ACharBase* CharacterOnTile;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ATileBase*> Neighs;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ATileBase*> AvailableNeighs;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
