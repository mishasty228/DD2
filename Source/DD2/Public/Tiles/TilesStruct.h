// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TileEnum.h"


#include "TilesStruct.generated.h"

class ATileBase;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FTilesStruct
{
	GENERATED_BODY()

	FORCEINLINE FTilesStruct();
	
	explicit FORCEINLINE FTilesStruct(int32 Row, int32 Col,
		FVector Loc, bool BAvailable, bool BVisited);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 RowIndex = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ColIndex = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Location = FVector(0,0,0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Available = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool Visited = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ETileType> TileType = ETT_Path;
	
	bool operator==(const FTilesStruct& A) const;
	bool operator!=(const FTilesStruct& A) const;
	
};

FORCEINLINE FTilesStruct::FTilesStruct()
{
	
}
FORCEINLINE FTilesStruct::FTilesStruct(const int32 Row,const int32 Col,
		const FVector Loc,const bool BAvailable,const bool BVisited)
{
	RowIndex = Row;
	ColIndex = Col;
	Location = Loc;
	Available = BAvailable;
	Visited = BVisited;
}

FORCEINLINE bool FTilesStruct::operator==(const FTilesStruct& A) const
{
	return RowIndex==A.RowIndex||ColIndex==A.ColIndex;
}
FORCEINLINE bool FTilesStruct::operator!=(const FTilesStruct& A) const
{
	return RowIndex!=A.RowIndex||ColIndex!=A.ColIndex;
}

FORCEINLINE uint32 GetTypeHash(const FTilesStruct& b)
{
	return FCrc::MemCrc_DEPRECATED(&b, sizeof(FTilesStruct));
}