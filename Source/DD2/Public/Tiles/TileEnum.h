// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TileEnum.generated.h"

UENUM(BlueprintType)
enum ETileType
{
	ETT_None UMETA(DisplayName="Nothing"),
	ETT_Wall UMETA(DisplayName="Barrier"),
	ETT_Path UMETA(DisplayName="Way"),
	ETT_Portal UMETA(DisplayName="Portal")
};