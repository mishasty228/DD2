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

	UFUNCTION(BlueprintCallable)
	bool TryToOpen(ACharBase* Char);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOpened=false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bLocked=false;
};
