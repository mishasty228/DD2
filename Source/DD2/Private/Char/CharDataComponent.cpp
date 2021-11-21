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
		CharData = FCharDataStruct(Names[FRandomStream().RandRange(0,Names.Num()-1)] ,FRandomStream().RandRange(18,22), FRandomStream().RandRange(8,12),
			FRandomStream().RandRange(4,6),FRandomStream().RandRange(5,7),
			FRandomStream().RandRange(5,25),FRandomStream().RandRange(4,6),
			1);
		break;
	default:
		CharData = FCharDataStruct(Names[FRandomStream().RandRange(0,Names.Num()-1)] ,FRandomStream().RandRange(18,22), FRandomStream().RandRange(8,12),
			FRandomStream().RandRange(4,6),FRandomStream().RandRange(5,7),
			FRandomStream().RandRange(5,25),FRandomStream().RandRange(4,6),
			1);
		break;
	}
	CharType = type;
}

