// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/Types/TileBase_Door.h"

bool ATileBase_Door::CharInteraction_Implementation(ACharBase* Char)
{
	if (TilesStruct.Interactable==true)
	{
		OpenDoor_Implementation();
		TilesStruct.Interactable = false;
	}
	return Super::CharInteraction_Implementation(Char);
}

void ATileBase_Door::OpenDoor_Implementation()
{
	//Mesh->SetVisibility(false);
	return;
}
