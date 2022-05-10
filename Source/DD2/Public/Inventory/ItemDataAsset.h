// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EItemTypes.h"
#include "Engine/DataAsset.h"
#include "Living/FActionEffect.h"
#include "Living/FLivingProperties.h"
#include "ItemDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TEnumAsByte<EItemType> ItemType = EIT_None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 Price=0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Description;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* Thumbnail = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UTexture2D* Logo = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool bStackable = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 Amount = 1;




};
