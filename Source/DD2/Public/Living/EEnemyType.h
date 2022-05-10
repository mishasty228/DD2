#pragma once

#include "EEnemyType.generated.h"

UENUM (BlueprintType)
enum EEnemyType
{
	EEnT_None UMETA(DisplayName = "None"),
	EEnT_Goblin UMETA(DisplayName="Goblin"),
	EEnT_Skeleton UMETA(DisplayName="Skeleton"),
	EEnT_Ifrit UMETA(DisplayName="Ifrit"),
	EEnT_Bandit UMETA(DisplayName="Bandit")
};
