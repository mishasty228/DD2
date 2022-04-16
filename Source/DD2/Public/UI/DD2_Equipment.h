// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DD2_Equipment.generated.h"

class AGameMaster;
/**
 * 
 */
UCLASS()
class DD2_API UDD2_Equipment : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	AGameMaster* Player;

private:

public:

};
