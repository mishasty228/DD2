// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Char/CharBase.h"
#include "GameFramework/PlayerController.h"
#include "DD2PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API ADD2PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<ACharBase*> Characters;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	ACharBase* CurrentCharacter;
};
