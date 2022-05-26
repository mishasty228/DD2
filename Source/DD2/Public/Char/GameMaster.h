// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DD2PlayerController.h"
#include "Living/FAction.h"
#include "GameFramework/Character.h"
#include "Tiles/TileMap.h"
#include "Char/CharBase.h"
#include "GameMaster.generated.h"


class ADD2HUD;
UCLASS()
class DD2_API AGameMaster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGameMaster();

	UWorld* world = GetWorld();

	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Characters")
	TArray<ACharBase*> Characters;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Characters")
	TArray<ACharBase*> CharactersForTurn;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Characters")
	ACharBase* CurrentCharacter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAction SelectedAction;
	
	UPROPERTY(BlueprintReadOnly)
	int32 AP=0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "GameplayDefaults")
	ADD2HUD* HUD;

	bool bCanSelect = true;
	bool bMoving = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ATileMap* Map;

	UPROPERTY()
	TArray<int32> AvailableIndexes;

	TArray<int32> Path;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ATileBase* SelectedTile;

	UPROPERTY()
	TArray <ATileBase*> AvailableTiles;

	UPROPERTY()
	int32 Turn;

	UPROPERTY(BlueprintReadOnly)
	ADD2PlayerController* PlayerController;

	bool CanRotate = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetNextChar();

	UFUNCTION(BlueprintCallable)
	void SelectTile();

	UFUNCTION(BlueprintCallable)
	void SelectAction(FAction Action);

	UFUNCTION(BlueprintCallable)
	void FirstHeroesSetup();
	
	UFUNCTION(BlueprintCallable)
	void SumHeroesUp();

	UFUNCTION(BlueprintCallable)
	void SortChars();

	void Select();
	
	void MoveCycle();

	void CheckLeft();

	void ClearAvailable();
	void ColorAvailable();

	void Camera_YAxis(float Value);
	void SpringDown();
	void SpringUp();
	
	void SetCanRotateTrue();
	void SetCanRotateFalse();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleInventory();
};
