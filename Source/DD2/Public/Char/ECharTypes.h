// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ECharTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum ECharType
{
    ECT_Knight UMETA(DisplayName="Knight"),
    ECT_Thief UMETA(DisplayName="Thief"),
    ECT_Spearman UMETA(DisplayName="Spearman"),
    ECT_Wizard UMETA(DisplayName="Wizard"),
    ECT_Paladin UMETA(DisplayName="Paladin"),
    ECT_Archer UMETA(DisplayName="Archer"),
    ECT_Alchemist UMETA(DisplayName="Alchemist")
};
