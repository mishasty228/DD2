// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DD2/DD2.h"
#include "DD2_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API UDD2_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UDD2_GameplayAbility();

	//Abilities will activate when input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Abilities")
	EDD2AbilityInputID AbilityInputID {EDD2AbilityInputID::None};
	
};
