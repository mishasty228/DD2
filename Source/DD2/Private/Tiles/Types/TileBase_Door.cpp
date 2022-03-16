// Fill out your copyright notice in the Description page of Project Settings.


#include "Tiles/Types/TileBase_Door.h"

bool ATileBase_Door::CharInteraction_Implementation(ACharBase* Char)
{
	if (!Super::CharInteraction_Implementation(Char) )
	{
		if (bLocked == true)
		{
			if (TryToOpen(Char))
			{
				bLocked =false;
				TilesStruct.Available = true;
				return false;
			}
		}
		else
		{
			if (!bOpened)
            {
            	OpenDoor_Implementation();
            	TilesStruct.Interactable = false;
            	TilesStruct.Available = true;
            	return false;
            }
		}
	}
	return true;
}

/**
 * @brief 
 * @param Char is to check its inventory for a key
 * @return if key is at backpack, then return true and remove 1 key from inventory
 */
bool ATileBase_Door::TryToOpen(ACharBase* Char)
{
	return true;
}

void ATileBase_Door::OpenDoor_Implementation()
{
	//Mesh->SetVisibility(false);
	return;
}
