// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Tiles/TileBase.h"
#include "FCharDataStruct.generated.h"

class ATileBase;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharDataStruct
{
 GENERATED_BODY()

 FORCEINLINE FCharDataStruct();

 explicit FORCEINLINE FCharDataStruct(FString name, int32 hp, int32 mp, int32 ap, int32 str, int32 spd, int32 def, int32 ar);

 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameters")
 FString Name = "None";
 
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameters")
 int32 HP = 20;

 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameters")
 int32 MP = 10;
 
 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameters")
 int32 AP = 4;

 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameters")
 int32 STR = 5;

 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameters")
 int32 SPD = 8;

 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameters")
 int32 DEF = 5;

 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameters")
 int32 AR = 1;

 /*UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameters")
 UTexture2D* Thumbnail;*/

 UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Parameters")
 TArray<ATileBase*> TilesInActionRange;
 
};

inline FCharDataStruct::FCharDataStruct()
{
}

inline FCharDataStruct::FCharDataStruct(FString name, int32 hp, int32 mp, int32 ap, int32 str, int32 spd, int32 def, int32 ar)
{
 Name = name;
 HP = hp;
 MP = mp;
 AP = ap;
 STR = str;
 SPD = spd;
 DEF = def;
 AR = ar;
}
