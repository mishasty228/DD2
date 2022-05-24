// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/ItemDataAsset.h"
#include "ArmorDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API UArmorDataAsset : public UItemDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TArray<USkeletalMesh*> ChestMeshVariations;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Health=0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Speed=0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamageResist = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DodgeChance = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FireResist = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float IceResist = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PoiseResist = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BleedResist = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StunResist = 0;
};
