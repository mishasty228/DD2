// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DD2HUD.h"
#include "Char/GameMaster.h"
#include "DD2PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "DD2GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API ADD2GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADD2GameModeBase();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	AGameMaster* GameMaster;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	ADD2HUD* HUD;
};
