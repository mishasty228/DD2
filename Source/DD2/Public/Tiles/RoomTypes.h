// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RoomTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum ERoomTypes
{
 ERT_Base UMETA(DisplayName="BasicRoom"),
 ERT_ChestRoom UMETA(DisplayName="RoomWithChest"),
 ERT_KeyRoom UMETA(DisplayName="RoomWithKey"),
 ERT_EnemyRoom UMETA(DisplayName="RoomWithEnemies"),
 ERT_PortalRoom UMETA(DisplayName="RoomWithPortal"),
 ERT_SpawnRoom UMETA(DisplayName="RoomWithSpawn"),
 ERT_ShopRoom UMETA(DisplayName="RoomWithShop")
};

