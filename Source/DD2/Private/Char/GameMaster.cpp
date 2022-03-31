// Fill out your copyright notice in the Description page of Project Settings.


#include "Char/GameMaster.h"

#include <fstream>


// Sets default values
AGameMaster::AGameMaster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameMaster::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<ADD2PlayerController>(GetWorld()->GetFirstPlayerController());
	PlayerController->SetShowMouseCursor(true);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameMaster::FirstHeroesSetup, 1.0f);
	
}



// Called to bind functionality to input
void AGameMaster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Mouse_X", this, &AGameMaster::Camera_YAxis);
	PlayerInputComponent->BindAction("SpringUp", IE_Pressed, this, &AGameMaster::SpringUp);
	PlayerInputComponent->BindAction("SpringDown", IE_Pressed, this, &AGameMaster::SpringDown);

	PlayerInputComponent->BindAction("Select", IE_Pressed, this, &AGameMaster::SelectTile);
	PlayerInputComponent->BindAction("NextChar", IE_Pressed, this, &AGameMaster::SetNextChar);
	
	PlayerInputComponent->BindAction("CameraRotation", IE_Pressed, this, &AGameMaster::SetCanRotateTrue);
	PlayerInputComponent->BindAction("CameraRotation", IE_Released, this, &AGameMaster::SetCanRotateFalse);
}

void AGameMaster::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Select();
}

void AGameMaster::SetNextChar()
{
	if (Characters.Num()>0)
	{
		if (CharactersForTurn.Num()>=1)
		{
			ATileBase* Tile;
			//ClearSelected
			if (SelectedTile) SelectedTile->ClearMatColor();
			if(CurrentCharacter)
			{
				Tile = Map->FindTileByIndex(CurrentCharacter->CurIndex);
				if (Tile) Tile->ClearMatColor();
			}
			ClearAvailable();
			
			
			CurrentCharacter = CharactersForTurn[0];
			AP = CurrentCharacter->ActionPoints;
			Tile = Map->FindTileByIndex(CurrentCharacter->CurIndex);
			if (Tile)
			{
				Tile->SetMatScalarParameter("Boost", 0.5f);
				Tile->SetMatVectorParameter("Emissive", FLinearColor(1,1,0,1));
			}
			PlayerController->SetViewTargetWithBlend(CurrentCharacter, 1.f);
			UE_LOG(LogTemp, Display, TEXT("%s character with speed %d"),
				*CurrentCharacter->Name, CurrentCharacter->SpeedPoints);
			CharactersForTurn.RemoveAt(0);
			AvailableTiles = Map->FindTilesReachable(CurrentCharacter->CurIndex, AP);
			ColorAvailable();
		}
		else
		{
			SumHeroesUp();
			SetNextChar();
		}
	}
	return;
}

void AGameMaster::SelectTile()
{
	if (SelectedTile)
	{
		const int32 index=SelectedTile->TilesStruct.aind;
		if (index==CurrentCharacter->CurIndex) return;
        const ATileBase* Tile = Map->FindTileByIndex(index);
        if (Tile)
        {
        	/*if (Tile->TilesStruct.TileType==ETT_Room || Tile->TilesStruct.TileType==ETT_Path ||
        		Tile->TilesStruct.TileType==ETT_Trap )
        	{
        		Path = Map->FindPathRoute(CurrentCharacter->CurIndex, index);
        	}
        	else if (Tile->TilesStruct.TileType==ETT_Chest || Tile->TilesStruct.TileType==ETT_Door ||
        		Tile->TilesStruct.TileType==ETT_Key || Tile->TilesStruct.TileType==ETT_Portal ||
        		Tile->TilesStruct.TileType==ETT_Shop)
        	{
        		Path = Map->FindPathRoute(CurrentCharacter->CurIndex, index);
        		Path.RemoveAt(Path.Num()-1);
        	}*/
        	Path = Map->FindPathRoute(CurrentCharacter->CurIndex, index, AP);
        	//Path.RemoveAt(0);
        	CurrentCharacter->Path = Path;
        	CurrentCharacter->Move();
        	//MoveCycle();
        }
	}
}

void AGameMaster::SelectAction(FAction Action)
{
	
}

void AGameMaster::FirstHeroesSetup()
{
	SortChars();
	CharactersForTurn = Characters;
	for (ACharBase* Char : Characters)
	{
		Char->GameMaster = this;
		Char->Map = Map;
		if (IsValid(Char))
		{
			//UE_LOG (LogTemp, Display, TEXT("This char's name is %s gm is %s and map is %s"), *Char->Name,
            //			*Char->GameMaster->GetName(),*Char->Map->GetName());
		}
		else UE_LOG(LogTemp,Warning,TEXT("No chars so far"));
	}
	return;
}


void AGameMaster::SumHeroesUp()
{
	SortChars();
	CharactersForTurn = Characters;
	return;
}

void AGameMaster::SortChars()
{
	if (Characters.Num()>0)
	{
		for (int32 i = 0; i < Characters.Num(); i++)
		{
			bool swapped = false;
			for (int32 j = Characters.Num()-1; j > i; j--)
			{
				if (Characters[j-1]->SpeedPoints<Characters[j]->SpeedPoints)
				{
					Characters.Swap(j,j-1);
					swapped = true;
				}
			}
			if (!swapped) break;
		}
		for (const ACharBase* Char : Characters)
		{
			UE_LOG(LogTemp, Display, TEXT("%s has speed %d"), *Char->Name, Char->SpeedPoints);
		}
	}
}


//Tile selection function
void AGameMaster::Select()
{
	if (bMoving) return;
	//LineTraceParams Setup
	FHitResult Hit = FHitResult();
	FVector startray = FVector().ZeroVector;
	FVector startdir = FVector().ZeroVector;
	FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, NULL);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = true;
	
	PlayerController->DeprojectMousePositionToWorld(startray, startdir);
	//UE_LOG(LogTemp, Display, TEXT("startray %f, %f, %f"), startray.X, startray.Y, startray.Z);
	//UE_LOG(LogTemp, Display, TEXT("startdir %f, %f, %f"), startdir.X, startdir.Y, startdir.Z);
	if (GetWorld()->LineTraceSingleByChannel(Hit, startray, startray+startdir*5000, ECC_GameTraceChannel3, TraceParams ))
	{
		ATileBase* HitActor = Cast<ATileBase>(Hit.Actor);
		if (SelectedTile)
		{
			if (SelectedTile->TilesStruct.aind!=CurrentCharacter->CurIndex)
			{
				SelectedTile->SetMatScalarParameter("Boost", 0.0f);
				SelectedTile->SetMatVectorParameter("Emissive", FLinearColor(1,1,1,1));
			}
		}
		ColorAvailable();
		if (HitActor)
		{
			/* (SelectedTile==HitActor)
			{
				Move();
			}
			*/
			SelectedTile = HitActor;
			if (AvailableTiles.Contains(HitActor))
			{
				if (AP>=Map->GetTDistance( SelectedTile->TilesStruct.aind))
				{
					UE_LOG(LogTemp,Display,TEXT("Good"));
					Path = Map->FindPathRoute(CurrentCharacter->CurIndex, SelectedTile->TilesStruct.aind, AP);
                    for (int32 i : Path)
                    {
                    	Map->FindTileByIndex(i)->SetMatScalarParameter("Boost", .5f);
                    	Map->FindTileByIndex(i)->SetMatVectorParameter("Emissive", FLinearColor().Blue);
                    }
				}
				
			}
			
		}
		else SelectedTile = nullptr;
	}
} 

void AGameMaster::MoveCycle()
{
	if (Path.Num()>0&&AP>0)
	{
		bMoving = true;
		const int32 ind = Path[0];
		ATileBase* indTile = Map->FindTileByIndex(ind);
		if (indTile)
		{
			Map->FindTileByIndex(CurrentCharacter->CurIndex)->TilesStruct.Available = true;
			if (indTile->TilesStruct.Interactable==false)
            {
                Path.RemoveAt(0);
            }
			if (indTile->CharInteraction(CurrentCharacter))
			{
				indTile->TilesStruct.Available = false;
			}
			AP--;
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameMaster::MoveCycle, 1.5f);
		}
		else UE_LOG(LogTemp,Display,TEXT("Couldn't find tile %i"));
	}
	else
	{
		bMoving = false;
		CheckLeft();
	}
	
}

void AGameMaster::CheckLeft()
{
	ClearAvailable();
	if (AP <=0) SetNextChar();
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Looking For Left Tiles"));
		AvailableTiles = Map->FindTilesReachable(CurrentCharacter->CurIndex, AP);
		ColorAvailable();
	}
	return;
}

void AGameMaster::ClearAvailable()
{
	for (ATileBase* T : AvailableTiles)
	{
		if (T) T->ClearMatColor();
	}
}

void AGameMaster::ColorAvailable()
{
	for (ATileBase* TileinMap : AvailableTiles)
	{
		TileinMap->SetMatScalarParameter("Boost", .5f);
		TileinMap->SetMatVectorParameter("Emissive", FLinearColor().Green);
		if (TileinMap->TilesStruct.aind==CurrentCharacter->CurIndex)
		{
			TileinMap->SetMatScalarParameter("Boost", .5f);
			TileinMap->SetMatVectorParameter("Emissive", FLinearColor().Yellow);
		}
	}
}

void AGameMaster::Camera_YAxis(float Value)
{
	if (CanRotate && CurrentCharacter)
	{
		CurrentCharacter->SpringArm->AddRelativeRotation(FRotator(0,Value,0));
	}
}

void AGameMaster::SpringDown()
{
	CurrentCharacter->SpringArm->TargetArmLength = FMath::Clamp(CurrentCharacter->SpringArm->TargetArmLength+25, 500.0f, 2000.0f);
}

void AGameMaster::SpringUp()
{
	CurrentCharacter->SpringArm->TargetArmLength = FMath::Clamp(CurrentCharacter->SpringArm->TargetArmLength-25, 500.0f, 2000.0f);
}

void AGameMaster::SetCanRotateTrue()
{
	CanRotate = true;
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(false);
		PlayerController->bCanSelect = false;
	}
}	
void AGameMaster::SetCanRotateFalse()
{
	CanRotate=false;
	if (PlayerController)
	{
		PlayerController->SetShowMouseCursor(true);
		PlayerController->bCanSelect = true;
	}
}