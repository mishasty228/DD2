// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/DD2_AttributeSet.h"

#include "Net/UnrealNetwork.h"

UDD2_AttributeSet::UDD2_AttributeSet()
{
}

void UDD2_AttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UDD2_AttributeSet, Health);
}

void UDD2_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UDD2_AttributeSet, Health, OldValue);
}
