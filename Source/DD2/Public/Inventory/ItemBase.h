// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS()
class DD2_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="ItemBase Parameters")
	int32 Price=0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="ItemBase Parameters")
	FName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="ItemBase Parameters")
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="ItemBase Parameters")
	UTexture2D* Thumbnail = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="ItemBase Parameters")
	UTexture2D* Logo = nullptr;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


};
