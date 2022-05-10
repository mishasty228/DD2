// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Inventory/ItemDataAsset.h"
#include "Living/EEnemyType.h"
#include "Living/FAction.h"
#include "EnemyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API UEnemyDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Visual")
	FString Name = "None";

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Parameters")
	TEnumAsByte<EEnemyType> CharType = EEnT_None;
 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Parameters")
	int32 HealthPoints=0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Parameters")
	int32 DamagePoints=0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Parameters")
	int32 ActionPoints=0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Parameters")
	int32 SpeedPoints=0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Actions")
	TArray<FAction> Actions;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float DamageResist = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float DodgeChance = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float FireResist = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float IceResist = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float PoiseResist = 0;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float BleedResist = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float StunResist = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Visual")
	UTexture2D* Thumbnail = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Visual")
	USkeletalMesh* Mesh = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Visual")
	UAnimationAsset* AnimationAsset = nullptr;

	UPROPERTY(BlueprintReadOnly,EditAnywhere, Category="Visual")
	TSubclassOf<AController> Controller = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Visual")
	TArray<TSubclassOf<UItemDataAsset>> Loot; 
	
};
