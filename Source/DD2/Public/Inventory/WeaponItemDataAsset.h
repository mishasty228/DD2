// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/ItemDataAsset.h"
#include "WeaponItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API UWeaponItemDataAsset : public UItemDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
    UStaticMesh* WeaponMesh;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
    int32 Damage;

	
};
