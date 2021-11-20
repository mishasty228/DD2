// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ECharTypes.h"
#include "FCharDataStruct.h"
#include "Components/ActorComponent.h"
#include "CharDataComponent.generated.h"

//class ATileBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DD2_API UCharDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharDataComponent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameters")
	FCharDataStruct CharData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameters")
	TEnumAsByte<ECharType> CharType = ECT_Knight;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Setter")
	void GenerateRandomParametersForType(TEnumAsByte<ECharType> type);
	
};
