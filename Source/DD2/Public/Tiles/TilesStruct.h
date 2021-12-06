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
	
	explicit FORCEINLINE FTilesStruct(FVector Loc, bool BAvailable, bool BVisited);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 r = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 q = 0;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 s = 0;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int32 aind = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Location = FVector(0,0,0);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	mutable bool Available = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	mutable bool Visited = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	mutable TEnumAsByte<ETileType> TileType = ETT_Path;
	
	bool operator==(const FTilesStruct& A) const;
	bool operator!=(const FTilesStruct& A) const;
	
};

FORCEINLINE FTilesStruct::FTilesStruct()
{
	
}
FORCEINLINE FTilesStruct::FTilesStruct(
		const FVector Loc,const bool BAvailable,const bool BVisited)
{
	Location = Loc;
	Available = BAvailable;
	Visited = BVisited;
}

FORCEINLINE bool FTilesStruct::operator==(const FTilesStruct& A) const
{
	return r==A.r&&q==A.q;
}
FORCEINLINE bool FTilesStruct::operator!=(const FTilesStruct& A) const
{
	return r!=A.r||q!=A.q;
}

FORCEINLINE uint32 GetTypeHash(const FTilesStruct& b)
{
	return FCrc::MemCrc_DEPRECATED(&b, sizeof(FTilesStruct));
}