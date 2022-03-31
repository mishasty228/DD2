#include "Enemy/EnemyBase.h"


AEnemyBase::AEnemyBase()
{
	
}

void AEnemyBase::InitializeEnemy(TEnumAsByte<EEnemyType> Type)
{
	switch (EnemyType)
	{
	case EET_Goblin:
		SetParameters(10,5,5,5,
			0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f);
		break;
	default:
		SetParameters(1,1,1,1,
			0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);
		break;
	}
}

void AEnemyBase::Move()
{
	Super::Move();
}
