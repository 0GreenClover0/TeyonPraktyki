// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiGameModeBase.h"

#include "PraktykiGameInstance.h"
#include "PraktykiPlayerController.h"

APraktykiGameModeBase::APraktykiGameModeBase()
{
	PlayerControllerClass = APraktykiPlayerController::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void APraktykiGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GameTime -= DeltaTime;
}

void APraktykiGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = GetGameInstance<UPraktykiGameInstance>();

	check(GameInstance);

	GameTime = GameInstance->GetMaxGameTime();
}
