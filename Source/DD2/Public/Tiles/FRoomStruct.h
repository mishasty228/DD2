#pragma once
#include "RoomTypes.h"

#include "FRoomStruct.generated.h"


class ATileBase;
USTRUCT(BlueprintType)

struct FRoomStruct
{
	GENERATED_BODY()

	FORCEINLINE FRoomStruct();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<ATileBase*> TilesArray;

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
};

inline FRoomStruct::FRoomStruct()
{
	
}
