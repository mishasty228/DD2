// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Living/FAction.h"
#include "Living/FActionEffect.h"
#include "GameFramework/Character.h"
#include "LivingBeing.generated.h"

class UNavigationInvokerComponent;
class ATileMap;
class ATileBase;


UCLASS()
class DD2_API ALivingBeing : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALivingBeing();

	UPROPERTY()
	ATileMap* Map = nullptr;

	UPROPERTY()
	FTimerHandle TimerHandle;

	ATileBase* NextTile = nullptr;

	TArray<int32> Path;

	bool StepSuccess = false;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 CurIndex=0;

	UPROPERTY(BlueprintReadWrite,Category="LivingBeing")
	int32 HealthPoints=1;

	UPROPERTY(BlueprintReadWrite,Category="LivingBeing")
	int32 DamagePoints=1;

	UPROPERTY(BlueprintReadWrite,Category="LivingBeing")
	int32 ActionPoints=1;

	UPROPERTY(BlueprintReadWrite,Category="LivingBeing")
	int32 SpeedPoints=1;

	UPROPERTY(BlueprintReadWrite,Category="LivingBeing")
	TArray<FAction> Actions;

	UPROPERTY(BlueprintReadWrite,Category="LivingBeing")
	TArray<FActionEffect> Effects = {FActionEffect(EET_None, 0, 0),
										FActionEffect(EET_Bleed, 0, 0),
										FActionEffect(EET_Flame, 0, 0),
										FActionEffect(EET_Freeze, 0, 0),
										FActionEffect(EET_Poise, 0, 0),
										FActionEffect(EET_Stun, 0, 0)};

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="View")
	UTexture2D* Thumbnail = nullptr;

	UPROPERTY(BlueprintReadWrite,Category="View")
	FString Name = "";

	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float DamageResist = 0;

	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float DodgeChance = 0;

	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float FireResist = 0;

	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float IceResist = 0;

	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float PoiseResist = 0;
	
	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float BleedResist = 0;

	UPROPERTY(BlueprintReadWrite,Category="Resists")
	float StunResist = 0;
	
	FRandomStream RandomStream;
	//FCharDataStruct CharDataStruct;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintCallable)
	void GetDamage(int32 damage);

	UFUNCTION(BlueprintCallable)
	void AddEffect(TEnumAsByte<EEffectTypes> effect, int32 damage, int32 duration, float chance);

	UFUNCTION(BlueprintCallable)
	void CheckEffects();

	UFUNCTION(BlueprintCallable)
	virtual void Move();

	UFUNCTION(BlueprintCallable)
	virtual void Step();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MoveToLocation(FVector Target);

	UFUNCTION(BlueprintCallable)
	virtual void DoAction();

	UFUNCTION(BlueprintCallable)
	virtual void SelectAction();

	UFUNCTION(BlueprintCallable)
	virtual void Interact(int32 Index);

	UFUNCTION(BlueprintCallable)
	virtual void StartTurn();

	UFUNCTION(BlueprintCallable)
	virtual void EndTurn();


	

	UFUNCTION(BlueprintCallable)
	void SetParameters(int32 hp, int32 dp, int32 ap, int32 sp,
		float dr, float dc, float fr, float ir, float pr, float br, float sr);
};
