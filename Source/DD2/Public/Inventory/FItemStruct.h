// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EItemTypes.h"
#include "Living/FActionEffect.h"
#include "Living/FLivingProperties.h"

#include "FItemStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FItemStruct
{
	GENERATED_BODY()

	FORCEINLINE FItemStruct();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EItemType> ItemType = EIT_None;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Price=0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Thumbnail = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Logo = nullptr;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bStackable = false;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 Amount = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USkeletalMesh* ArmorMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* WeaponMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FActionEffect Effect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLivingProperties LivingProperties;
};

inline FItemStruct::FItemStruct()
{
}
