// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TilesStruct.generated.h"

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
	
	UPROPERTY(BlueprintReadWrite)
	int32 RowIndex = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 ColIndex = 0;

	UPROPERTY(BlueprintReadWrite)
	FVector Location = FVector(0,0,0);

	UPROPERTY(BlueprintReadWrite)
	bool Available = true;

	UPROPERTY(BlueprintReadWrite)
	bool Visited = false;
	
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