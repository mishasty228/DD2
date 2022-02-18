#pragma once
#include "EEffectTypes.h"

#include "FActionEffect.generated.h"

/**
 * @brief This struct is used to store effects on character by type
 */
USTRUCT(BlueprintType)

struct FActionEffect
{
	GENERATED_BODY()
	
	FORCEINLINE FActionEffect();
	
	FORCEINLINE FActionEffect(TEnumAsByte<EEffectTypes> Type, int32 Dmg, int32 Dur);

	void SetDuration(int32 duration);

	void SetDamage(int32 damage);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<EEffectTypes> EffectType = EET_None;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 Damage = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 Duration = 0;
};

inline FActionEffect::FActionEffect()
{
	
}

inline FActionEffect::FActionEffect(TEnumAsByte<EEffectTypes> Type, int32 Dmg, int32 Dur)
{
	EffectType = Type;
	Damage = Dmg;
	Duration = Dur;
}

inline void FActionEffect::SetDuration(int32 duration)
{
	Duration = duration;
}

inline void FActionEffect::SetDamage(int32 damage)
{
	Damage = damage;
}
