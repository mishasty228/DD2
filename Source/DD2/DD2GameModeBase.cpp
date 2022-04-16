// Copyright Epic Games, Inc. All Rights Reserved.


#include "DD2GameModeBase.h"


ADD2GameModeBase::ADD2GameModeBase()
{
	PlayerControllerClass = ADD2PlayerController::StaticClass();
	DefaultPawnClass = AGameMaster::StaticClass();
	HUDClass = ADD2HUD::StaticClass();
}


