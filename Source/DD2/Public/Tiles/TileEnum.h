// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TileEnum.generated.h"

UENUM(BlueprintType)
enum ETileType
{
	ETT_None UMETA(DisplayName="Nothing"),
	ETT_Wall UMETA(DisplayName="Barrier"),
	ETT_Block UMETA(DisplayName="Block"),
	ETT_Path UMETA(DisplayName="Way"),
	ETT_Portal UMETA(DisplayName="Portal"),
	ETT_Spawn UMETA(DisplayName="Spawn"),
	ETT_Door UMETA(DisplayName="Door"),
	ETT_Room UMETA(DisplayName="Room"),
	ETT_PreWallRoom UMETA(DisplayName="PreWallRoom"),
	ETT_Trap UMETA(DisplayName="Trap"),
	ETT_Shop UMETA(DisplayName="Shop"),
	ETT_Key UMETA(DisplayName="Key"),
	ETT_Chest UMETA(DisplayName="Chest"),
	ETT_EnemySpawn UMETA(DisplayName="Enemy"),
	ETT_Last UMETA(DisplayName="Last")
};