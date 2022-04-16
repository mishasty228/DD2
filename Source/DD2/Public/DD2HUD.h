// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Char/GameMaster.h"
#include "GameFramework/HUD.h"
#include "UI/DD2_Equipment.h"
#include "UI/DD2_HUD.h"
#include "UI/DD2_Inventory.h"
#include "DD2HUD.generated.h"

/**
 * 
 */
UCLASS()
class DD2_API ADD2HUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	AGameMaster* GameMaster;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Classes")
	TSubclassOf<UDD2_HUD> WHUD;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widgets")
	UDD2_HUD* HUD;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Classes")
	TSubclassOf<UDD2_Inventory> WInventory;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widgets")
	UDD2_Inventory* Inventory;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widget Classes")
	TSubclassOf<UDD2_Equipment> WEquipment;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Widgets")
	UDD2_Equipment* Equipment;
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CreateHud();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ShowHUDWidget(bool Show);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CreateInventory();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ShowInventoryWidget(bool Show);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CreateEquipment();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ShowEquipmentWidget(bool Show);
};
