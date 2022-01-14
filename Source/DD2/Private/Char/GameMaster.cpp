// Fill out your copyright notice in the Description page of Project Settings.


#include "Char/GameMaster.h"


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
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGameMaster::SumHeroesUp, 1.0f);
}

// Called every frame
void AGameMaster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameMaster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Mouse_Y", this, &AGameMaster::Camera_YAxis);
	PlayerInputComponent->BindAction("SpringUp", IE_Pressed, this, &AGameMaster::SpringUp);
	PlayerInputComponent->BindAction("SpringDown", IE_Pressed, this, &AGameMaster::SpringDown);

	PlayerInputComponent->BindAction("Select", IE_Pressed, this, &AGameMaster::Select);
	PlayerInputComponent->BindAction("NextChar", IE_Pressed, this, &AGameMaster::SetNextChar);
	
	PlayerInputComponent->BindAction("CameraRotation", IE_Pressed, this, &AGameMaster::SetCanRotateTrue);
	PlayerInputComponent->BindAction("CameraRotation", IE_Released, this, &AGameMaster::SetCanRotateFalse);
}

void AGameMaster::SetNextChar()
{
	if (Characters.Num()>0)
	{
		if (CharactersForTurn.Num()>=1)
		{
			ATileBase* Tile;
			if (SelectedTile)
			{
				SelectedTile->SetMatScalarParameter("Boost", 0.0f);
				SelectedTile->SetMatVectorParameter("Emissive", FLinearColor(1,1,1,1));
			}
			if(CurrentCharacter)
			{
				Tile = Map->FindTileByIndex(CurrentCharacter->CurIndex);
				if (Tile)
				{
					Tile->SetMatScalarParameter("Boost", 0.0f);
					Tile->SetMatVectorParameter("Emissive", FLinearColor(1,1,1,1));
				}
			}
			CurrentCharacter = CharactersForTurn[0];
			Tile = Map->FindTileByIndex(CurrentCharacter->CurIndex);
			if (Tile)
			{
				Tile->SetMatScalarParameter("Boost", 0.5f);
				Tile->SetMatVectorParameter("Emissive", FLinearColor(1,1,0,1));
			}
			PlayerController->SetViewTargetWithBlend(CurrentCharacter, 1.f);
			UE_LOG(LogTemp, Display, TEXT("%s character with speed %d"),
				*CurrentCharacter->CharDataComponent->CharData.Name, CurrentCharacter->CharDataComponent->CharData.SPD);
			CharactersForTurn.RemoveAt(0);
			for (ATileBase* TileinMap : Map->FindTilesInRange(CurrentCharacter->CurIndex, CurrentCharacter->CharDataComponent->CharData.AP))
			{
				if (TileinMap->TilesStruct.Available)
				{
					TileinMap->SetMatScalarParameter("Boost", .5f);
					TileinMap->SetMatVectorParameter("Emissive", FLinearColor().Blue);
				}
				else
				{
					TileinMap->SetMatScalarParameter("Boost", .5f);
					TileinMap->SetMatVectorParameter("Emissive", FLinearColor().Red);
				}
				if (TileinMap->TilesStruct.aind==CurrentCharacter->CurIndex)
				{
					TileinMap->SetMatScalarParameter("Boost", .5f);
					TileinMap->SetMatVectorParameter("Emissive", FLinearColor().Yellow);
				}
			}
			
		}
		else
		{
			SumHeroesUp();
			SetNextChar();
		}
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


//Tile selection function
void AGameMaster::Select()
{
	//LineTraceParams Setup
	FHitResult Hit = FHitResult();
	FVector startray = FVector().ZeroVector;
	FVector startdir = FVector().ZeroVector;
	FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, NULL);
	TraceParams.bTraceComplex = true;
	TraceParams.bReturnPhysicalMaterial = true;
	
	PlayerController->DeprojectMousePositionToWorld(startray, startdir);
	UE_LOG(LogTemp, Display, TEXT("startray %f, %f, %f"), startray.X, startray.Y, startray.Z);
	UE_LOG(LogTemp, Display, TEXT("startdir %f, %f, %f"), startdir.X, startdir.Y, startdir.Z);
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
		if (HitActor)
		{
			SelectedTile = HitActor;
			if (SelectedTile->TilesStruct.Available)
			{
				SelectedTile->SetMatScalarParameter("Boost", .5f);
				SelectedTile->SetMatVectorParameter("Emissive", FLinearColor().Blue);
			}
			else
			{
				SelectedTile->SetMatScalarParameter("Boost", .5f);
				SelectedTile->SetMatVectorParameter("Emissive", FLinearColor().Red);
			}
			if (SelectedTile->TilesStruct.aind==CurrentCharacter->CurIndex)
            {
            	SelectedTile->SetMatScalarParameter("Boost", .5f);
            	SelectedTile->SetMatVectorParameter("Emissive", FLinearColor().Yellow);
            }
		}
		else SelectedTile = nullptr;
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