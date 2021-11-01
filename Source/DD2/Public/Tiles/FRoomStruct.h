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

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 size = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ERoomTypes> RoomType = ERT_Base;
};

inline FRoomStruct::FRoomStruct()
{
	
}
