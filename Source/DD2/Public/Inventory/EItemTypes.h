// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EItemTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EItemType
{
	EIT_None,
    EIT_Armor UMETA(DisplayName="Armor"),
    EIT_Weapon UMETA(DisplayName="Weapon"),
    EIT_Talisman UMETA(DisplayName="Talisman"),
    EIT_Consumable UMETA(DisplayName="Consumable"),
    EIT_Checkable UMETA(DisplayName="Checkable"),
	EIT_Money UMETA(DisplayName="Money")
};
