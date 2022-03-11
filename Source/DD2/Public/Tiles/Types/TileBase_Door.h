// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tiles/TileBase.h"
#include "TileBase_Door.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API ATileBase_Door : public ATileBase
{
	GENERATED_BODY()

public:
	virtual bool CharInteraction_Implementation(ACharBase* Char) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OpenDoor();
};
