// Fill out your copyright notice in the Description page of Project Settings.


#include "DD2HUD.h"

#include "AudioMixerDevice.h"
#include "Blueprint/UserWidget.h"

void ADD2HUD::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("HUD Begin Play"));
	GameMaster = Cast<AGameMaster>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CreateHud();
	ShowHUDWidget(true);
	CreateEquipment();
	CreateInventory();
}

void ADD2HUD::CreateInventory_Implementation()
{
	if (IsValid(WInventory))
	{
		Inventory = StaticCast<UDD2_Inventory*>(CreateWidget(GetWorld(), WInventory, "Inventory"));
	}
	if (IsValid(GameMaster)&& IsValid(Inventory)) Inventory->Player = GameMaster;
}

void ADD2HUD::ShowInventoryWidget_Implementation(bool Show)
{
	if (Inventory)
	{
		if (Show)
		{
			ShowHUDWidget_Implementation(false);
			Inventory->AddToViewport();
			UE_LOG(LogTemp, Display, TEXT("Inventory is shown"));
			return;
		}
		Inventory->RemoveFromParent();
		ShowHUDWidget_Implementation(true);
		UE_LOG(LogTemp, Display, TEXT("Inventory is hid"));
	}	
}

void ADD2HUD::CreateEquipment_Implementation()
{
	if (IsValid(WEquipment))
	{
		Equipment = StaticCast<UDD2_Equipment*>(CreateWidget(GetWorld(), WEquipment, "Equipment"));
	}
	if (IsValid(GameMaster)&& IsValid(Equipment)) Equipment->Player = GameMaster;
}

void ADD2HUD::ShowEquipmentWidget_Implementation(bool Show)
{
	ShowInventoryWidget_Implementation(Show);
	if (Equipment)
	{
		if (Show)
		{
			Equipment->AddToViewport();
			return;
		}
		Equipment->RemoveFromParent();
	}	
}

void ADD2HUD::CreateHud_Implementation()
{
	if (IsValid(WHUD))
 	{
 		HUD = StaticCast<UDD2_HUD*>(CreateWidget(GetWorld(), WHUD, "HUD"));
		UE_LOG(LogTemp, Display, TEXT("HUD created"));
 	}
	else UE_LOG(LogTemp, Warning, TEXT("WHUD is not valid"));
	if (IsValid(GameMaster) && IsValid(HUD))
	{
		HUD->Player = GameMaster;
		GameMaster->HUD = this;
		UE_LOG(LogTemp, Display, TEXT("HUD Player property is set up"));
	}
	else UE_LOG(LogTemp, Warning, TEXT("GM is not valid"));
}

void ADD2HUD::ShowHUDWidget_Implementation(bool Show)
{
	if (HUD)
	{
		if (Show)
		{
			HUD->AddToViewport();
			UE_LOG(LogTemp, Display, TEXT("HUD shown"));
			return;
		}
		HUD->RemoveFromParent();
		UE_LOG(LogTemp, Display, TEXT("HUD hid"));
	}	
}





