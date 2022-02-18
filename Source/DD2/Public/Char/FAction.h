#pragma once
#include "EActionTypes.h"
#include "EEffectTypes.h"

#include "FAction.generated.h"

USTRUCT(BlueprintType)
struct FAction
{
	GENERATED_BODY()

	FORCEINLINE FAction();

	FORCEINLINE FAction(FString name, TEnumAsByte<EActionTypes> EAT, TEnumAsByte<EEffectTypes> EET,
		int32 range, int32 damage, int32 reset_turns, int32 effect_duration, float effect_chance);

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FString Name = "None";

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EActionTypes> ActionType = EAT_CloseAttack;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EEffectTypes> EffectType = EET_None;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 Range = 1;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 Damage = 0;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 ResetTurns = 1;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 EffectDuration = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EffectChance = 0;
	
};

inline FAction::FAction()
{
}

inline FAction::FAction(FString name, TEnumAsByte<EActionTypes> EAT, TEnumAsByte<EEffectTypes> EET, int32 range,
	int32 damage, int32 reset_turns, int32 effect_duration, float effect_chance)
{
	Name = name;
	ActionType = EAT;
	EffectType = EET;
	Range = range;
	Damage = damage;
	ResetTurns = reset_turns;
	EffectDuration = effect_duration;
	EffectChance = effect_chance;
}

