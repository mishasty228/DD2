// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD2PlayerController.h"
#include "GameFramework/Character.h"
#include "Tiles/TileMap.h"
#include "Char/CharBase.h"
#include "GameMaster.generated.h"




UCLASS()
class DD2_API AGameMaster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameMaster();

	UWorld* world = GetWorld();

	FTimerHandle TimerHandle;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<ACharBase*> Characters;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<ACharBase*> CharactersForTurn;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	ACharBase* CurrentCharacter;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	AGameMaster* GameMaster;

	bool bCanSelect = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ATileMap* Map;

	UPROPERTY()
	TArray<int32> AvailableIndexes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ATileBase* SelectedTile;

	UPROPERTY()
	int32 Turn;

	UPROPERTY(BlueprintReadOnly)
	ADD2PlayerController* PlayerController;

	bool CanRotate = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetNextChar();
	
	UFUNCTION(BlueprintCallable)
	void SumHeroesUp();

	UFUNCTION(BlueprintCallable)
	void SortChars();

	void Select();

	void Camera_YAxis(float Value);
	void SpringDown();
	void SpringUp();
	
	void SetCanRotateTrue();
	void SetCanRotateFalse();
};
