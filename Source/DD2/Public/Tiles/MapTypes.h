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

inline int32 ClampInt(int32 value, int32 min, int32 max)
{
 if (min>max)
 {
  int32 tmp = min;
  min = max;
  max = tmp;
 }
 if (value < min) return min;
 if (value > max) return max;
 return value;
}
