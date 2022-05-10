#pragma once
#include "FAction.h"

#include "FLivingProperties.generated.h"

USTRUCT(BlueprintType)
struct FLivingProperties
{
	GENERATED_BODY()

	FORCEINLINE FLivingProperties();

	FORCEINLINE FLivingProperties(int32 hp, int32 dp, int32 ap, int32 sp, FAction A, float dr,
		float dc, float fr, float ir, float pr, float br, float sr);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 HealthPoints=0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 DamagePoints=0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ActionPoints=0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 SpeedPoints=0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FAction> Actions;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamageResist = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DodgeChance = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FireResist = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float IceResist = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float PoiseResist = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BleedResist = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StunResist = 0;
	
};

inline FLivingProperties::FLivingProperties()
{
}

inline FLivingProperties::FLivingProperties(int32 hp, int32 dp, int32 ap, int32 sp, FAction A, float dr, float dc,
	float fr, float ir, float pr, float br, float sr)
{
	HealthPoints = hp;
	DamagePoints = dp;
	ActionPoints = ap;
	SpeedPoints = sp;
	Actions.Add(A);
	DamageResist = dr;
	DodgeChance = dc;
	FireResist = fr;
	IceResist = ir;
	PoiseResist = pr;
	BleedResist = br;
	StunResist = sr;
}
