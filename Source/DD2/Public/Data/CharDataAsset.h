// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Living/ECharTypes.h"
#include "Living/FAction.h"
#include "CharDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API UCharDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Visual")
	FString Name = "None";

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Parameters")
	TEnumAsByte<ECharType> CharType = ECT_None;
 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Parameters")
	int32 HealthPoints=0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Parameters")
	int32 DamagePoints=0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Parameters")
	int32 ActionPoints=0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Parameters")
	int32 SpeedPoints=0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Actions")
	TArray<FAction> Actions;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float DamageResist = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float DodgeChance = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float FireResist = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float IceResist = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float PoiseResist = 0;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float BleedResist = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Resists")
	float StunResist = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Visual")
	UTexture2D* Thumbnail = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Visual")
	USkeletalMesh* Mesh = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Visual")
	UAnimationAsset* AnimationAsset = nullptr;

	
};
