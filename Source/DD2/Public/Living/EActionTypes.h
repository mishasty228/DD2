// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EActionTypes
{
	EAT_Walk UMETA(DisplayName="Walk"),
	EAT_CloseAttack UMETA(DisplayName="CloseCombat"),
	EAT_DistancedAttack UMETA(DisplayName="DistancedCombat"),
	EAT_AreaOfEffect UMETA(DisplayName="AoE"),
	EAT_BeamAttack UMETA(DisplayName="Beam")
};