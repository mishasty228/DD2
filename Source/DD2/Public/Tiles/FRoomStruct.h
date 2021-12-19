#pragma once
#include "RoomTypes.h"

#include "FRoomStruct.generated.h"


class ATileBase;
USTRUCT(BlueprintType)

struct FRoomStruct
{
	GENERATED_BODY()

	FORCEINLINE FRoomStruct();

	FORCEINLINE FRoomStruct(TEnumAsByte<ERoomTypes> Type);
	
	FORCEINLINE FRoomStruct(TEnumAsByte<ERoomTypes> Type, int32 Size, FVector2D Start, int32 enemies);

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<int32> WayTilesArray;

	/*UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<TEnumAsByte<ETileType>> TileTypes;*/

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<int32> cornerInd;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 size = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ERoomTypes> RoomType = ERT_Base;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FVector2D start = FVector2D(0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Enemies = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bGoFurther = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bLocked = false;

	void CheckType(TEnumAsByte<ERoomTypes> TypeRoom);
};

inline FRoomStruct::FRoomStruct()
{
	
}

inline FRoomStruct::FRoomStruct(TEnumAsByte<ERoomTypes> Type)
{
	CheckType(Type);
}

inline FRoomStruct::FRoomStruct(TEnumAsByte<ERoomTypes> Type, int32 Size, FVector2D Start, int32 enemies)
{
	CheckType(Type);
	size = Size;
	start = Start;
	Enemies = enemies;
	if (Type == ERT_KeyRoom) Enemies+=2;
}

inline void FRoomStruct::CheckType(TEnumAsByte<ERoomTypes> TypeRoom)
{
	RoomType = TypeRoom;
	if (TypeRoom == ERT_ChestRoom || TypeRoom == ERT_ShopRoom)
	{
		Enemies = 0;
		bLocked = true;
		bGoFurther = false;
	}
	else if (TypeRoom == ERT_KeyRoom)
	{
		Enemies = FRandomStream().RandRange(5,6);
	}
	else if (TypeRoom == ERT_EnemyRoom)
	{
		Enemies = FRandomStream().RandRange(4,5);
	}
}
