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
 ERT_PortalRoom UMETA(DisplayName="RoomWithPortal")
};

