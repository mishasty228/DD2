// Fill out your copyright notice in the Description page of Project Settings.


#include "Char/CharDataComponent.h"

// Sets default values for this component's properties
UCharDataComponent::UCharDataComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
	// ...
}


// Called when the game starts
void UCharDataComponent::BeginPlay()
{
	Super::BeginPlay();
	RandomStream.GenerateNewSeed();
	// ...
	
}


// Called every frame
void UCharDataComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharDataComponent::GenerateRandomParametersForType(TEnumAsByte<ECharType> type)
{
	switch (type)
	{
	case ECT_Wizard :
		CharData = FCharDataStruct(Names[RandomStream.RandRange(0,Names.Num()-1)] ,RandomStream.RandRange(18,22), RandomStream.RandRange(8,12),
			RandomStream.RandRange(3,5),RandomStream.RandRange(5,7),
			RandomStream.RandRange(5,25),RandomStream.RandRange(4,6),
			1);
		break;
	default:
		CharData = FCharDataStruct(Names[RandomStream.RandRange(0,Names.Num()-1)] ,RandomStream.RandRange(18,22), RandomStream.RandRange(8,12),
			RandomStream.RandRange(2,4),RandomStream.RandRange(5,7),
			RandomStream.RandRange(5,15),RandomStream.RandRange(4,6),
			1);
		break;
	}
	CharType = type;
}

