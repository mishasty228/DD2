// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EEffectTypes
{
	EET_None UMETA(DisplayName="FlatDamage"),
	EET_Flame UMETA(DisplayName="FireEffect"),
	EET_Freeze UMETA (DisplayName="IceEffect"),
	EET_Bleed UMETA (DisplayName="BleedEffect"),
	EET_Poise UMETA (DisplayName="PoisonEffect"),
	EET_Stun UMETA (DisplayName="StunEffect")
};