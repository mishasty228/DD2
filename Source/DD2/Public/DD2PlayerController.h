// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DD2PlayerController.generated.h"

class ACharBase;
class AGameMaster;
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
	TArray<ACharBase*> CharactersForTurn;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	ACharBase* CurrentCharacter;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	AGameMaster* GameMaster;

public:
	UFUNCTION(BlueprintCallable)
	void SetNextChar();

	UFUNCTION(BlueprintCallable)
	void SumHeroesUp();

	UFUNCTION(BlueprintCallable)
	void SortChars();
};
