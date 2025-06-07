// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiGameModeBase.h"

#include "PraktykiPlayerController.h"

APraktykiGameModeBase::APraktykiGameModeBase()
{
	PlayerControllerClass = APraktykiPlayerController::StaticClass();
}
