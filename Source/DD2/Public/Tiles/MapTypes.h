// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MapTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EMapTypes
{
 EMT_Base UMETA(DisplayName = "Basic Dungeon"),
 EMT_Snow UMETA(DisplayName = "SnowyDungeon"),
 EMT_Lava UMETA(DisplayName = "LavaDungeon")
};

