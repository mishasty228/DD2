// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ECharTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum ECharType
{
	ECT_None UMETA(DisplayName = "None"),
    ECT_Knight UMETA(DisplayName="Knight"),
    ECT_Spearman UMETA(DisplayName="Spearman"),
    ECT_Archer UMETA(DisplayName="Archer"),
    ECT_Wizard UMETA(DisplayName="Wizard"),
	ECT_Alchemist UMETA(DisplayName="Alchemist"),
	ECT_Bard UMETA (DisplayName="Bard"),
	ECT_Barbarian UMETA (DisplayName="Barbarian"),
	ECT_Necromancer UMETA (DisplayName="Necromancer"),
    ECT_Hunter UMETA(DisplayName="Hunter")
};
