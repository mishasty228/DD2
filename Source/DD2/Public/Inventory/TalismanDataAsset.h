// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/ItemDataAsset.h"
#include "TalismanDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API UTalismanDataAsset : public UItemDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FLivingProperties LivingProperties;
};
