// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CharDataComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Inventory/FItemStruct.h"
#include "Living/LivingBeing.h"
#include "CharBase.generated.h"

class AGameMaster;
class ADD2PlayerController;
class ATileBase;

UCLASS()
class DD2_API ACharBase : public ALivingBeing
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharBase();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Names")
	TArray<FString> Names = {"Debchik", "Dodik", "Kretin", "Loshped", "Gremlinus", "Durachok", "Baranid", "Kurdyuck"};
	
	UPROPERTY()
	AGameMaster* GameMaster=nullptr;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Components")
	USceneComponent* Scene;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Components")
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<ECharType> HeroType = ECT_Knight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Inventory")
	TArray<FItemStruct> Inventory;

	const int32 InventorySlots = 12;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void InitializeHero(TEnumAsByte<ECharType> Type);

	virtual void Move() override;

	virtual void Step() override;

	virtual void StartTurn() override;

	virtual void EndTurn() override;
};


