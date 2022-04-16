// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/ItemBase.h"
#include "UsableItem.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API AUsableItem : public AItemBase
{
	GENERATED_BODY()

	virtual void Use();
};
