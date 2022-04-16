// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/ItemBase.h"
#include "EquippableItem.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API AEquippableItem : public AItemBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,Category="LivingBeing")
	int32 HealthPoints=1;

	UPROPERTY(BlueprintReadWrite,Category="LivingBeing")
	int32 DamagePoints=1;

	UPROPERTY(BlueprintReadWrite,Category="LivingBeing")
	int32 ActionPoints=1;

	UPROPERTY(BlueprintReadWrite,Category="LivingBeing")
	int32 SpeedPoints=1;

	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float DamageResist = 0;

	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float DodgeChance = 0;

	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float FireResist = 0;

	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float IceResist = 0;

	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float PoiseResist = 0;
	
	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float BleedResist = 0;

	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float StunResist = 0;
	
};
