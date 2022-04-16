// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Usables/CheckableItem.h"
#include "Tiles/Types/TileBase_Container.h"
#include "TileBase_Key.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API ATileBase_Key : public ATileBase_Container
{
	GENERATED_BODY()

public:
	ATileBase_Key();

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Key")
	FItemStruct Key;
	
protected:
	virtual void BeginPlay() override;
};
