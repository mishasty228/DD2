// Fill out your copyright notice in the Description page of Project Settings.


#include "DD2PlayerController.h"

#include "../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/spdlog/include/spdlog/fmt/bundled/format.h"
#include "Char/CharBase.h"

void ADD2PlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (bCanSelect) SetShowMouseCursor(true);
	
}

void ADD2PlayerController::SetNextChar()
{
	if (Characters.Num()>0)
	{
		if (CharactersForTurn.Num()>=1)
		{
			if (CurrentCharacter) CurrentCharacter->SetPlayerController(nullptr);
			CurrentCharacter = CharactersForTurn[0];
			this->SetViewTargetWithBlend(CurrentCharacter, 1.f);
			UnPossess();
			Possess(CurrentCharacter);
			CurrentCharacter->SetPlayerController(this);
			UE_LOG(LogTemp, Display, TEXT("%s character with speed %d"),
				*CurrentCharacter->CharDataComponent->CharData.Name, CurrentCharacter->CharDataComponent->CharData.SPD);
		
			CharactersForTurn.RemoveAt(0);
		}
		else SumHeroesUp();
	}
	return;
}

void ADD2PlayerController::SumHeroesUp()
{
	SortChars();
	CharactersForTurn = Characters;
	return;
}

void ADD2PlayerController::SortChars()
{
	if (Characters.Num()>0)
	{
		for (int32 i = 0; i < Characters.Num(); i++)
        	{
        		bool swapped = false;
        		for (int32 j = Characters.Num()-1; j > i; j--)
        		{
        			if (Characters[j-1]->CharDataComponent->CharData.SPD<Characters[j]->CharDataComponent->CharData.SPD)
        			{
        				Characters.Swap(j,j-1);
        				swapped = true;
        			}
        		}
        		if (!swapped) break;
        	}
        for (ACharBase* Char : Characters)
        {
        	UE_LOG(LogTemp, Display, TEXT("%s has speed %d"), *Char->CharDataComponent->CharData.Name, Char->CharDataComponent->CharData.SPD);
        }
	}
}
