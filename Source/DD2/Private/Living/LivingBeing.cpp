// Fill out your copyright notice in the Description page of Project Settings.


#include "Living/LivingBeing.h"

// Sets default values
ALivingBeing::ALivingBeing()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ALivingBeing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALivingBeing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALivingBeing::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ALivingBeing::Die()
{
	Destroy();
}

void ALivingBeing::GetDamage(int32 damage)
{
	HealthPoints-=damage;
	if (HealthPoints<=0) Die();
}

void ALivingBeing::AddEffect(TEnumAsByte<EEffectTypes> effect, int32 damage, int32 duration, float chance)
{
	float resist;
	switch (effect)
	{
	case EET_None:
		resist = DamageResist;
		break;
	case EET_Flame:
		resist = FireResist;
		break;
	case EET_Freeze:
		resist = IceResist;
		break;
	case EET_Bleed:
		resist = BleedResist;
		break;
	case EET_Poise:
		resist = PoiseResist;
		break;
	case EET_Stun:
		resist = StunResist;
		break;
	default:
		resist = 0;
		break;
	}
	if (FMath::FRand()<(1-resist)*chance)
	{
		for (FActionEffect Effect : Effects)
		{
			if (Effect.EffectType==effect)
			{
				Effect.SetDamage(FMath::Max(Effect.Damage, damage));
				Effect.SetDuration(Effect.Duration+duration);
				break;
			}
		}
	}
}

void ALivingBeing::CheckEffects()
{
	for (FActionEffect Effect : Effects)
	{
		if (Effect.Duration>0)
		{
			GetDamage(Effect.Damage);
			Effect.SetDuration(Effect.Duration-1);
			if (Effect.EffectType==EET_Stun) EndTurn();
		}
		else Effect.SetDamage(0);
	}
}

void ALivingBeing::Move(TArray<int32> Path)
{
	
}

bool ALivingBeing::Step(ATileBase* Tile)
{
	return true;
}

void ALivingBeing::MoveToLocation_Implementation(FVector Target)
{
	
}

void ALivingBeing::DoAction()
{
	
}

void ALivingBeing::SelectAction()
{
	
}

void ALivingBeing::Interact(int32 Index)
{
	
}

void ALivingBeing::StartTurn()
{
	CheckEffects();
}

void ALivingBeing::EndTurn()
{
	
}

void ALivingBeing::SetParameters(int32 hp, int32 dp, int32 ap, int32 sp, 
                                 float dr,float dc,  float fr, float ir, float pr, float br, float sr)
{
	HealthPoints = hp;
	DamagePoints = dp;
	ActionPoints = ap;
	SpeedPoints = sp;
	DamageResist = dr;
	DodgeChance = dc;
	FireResist = fr;
	IceResist = ir;
	PoiseResist = pr;
	BleedResist = br;
	StunResist = sr;
}

