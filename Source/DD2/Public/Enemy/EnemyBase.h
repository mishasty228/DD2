// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Living/EEnemyType.h"
#include "Living/LivingBeing.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API AEnemyBase : public ALivingBeing
{
	GENERATED_BODY()
public:
	AEnemyBase();

	

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EEnemyType> EnemyType = EET_Goblin;

	UFUNCTION(BlueprintCallable)
	void InitializeEnemy(TEnumAsByte<EEnemyType> Type);

	virtual void Move(TArray<int32> Path) override;
};
