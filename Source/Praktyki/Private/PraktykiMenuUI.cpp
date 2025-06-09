// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiMenuUI.h"

#include "PraktykiGameInstance.h"

void UPraktykiMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	GameInstance = GetGameInstance<UPraktykiGameInstance>();
}

void UPraktykiMenuUI::SetMaxTime(float Time)
{
	GameInstance->SetMaxGameTime(Time);
}

void UPraktykiMenuUI::SetLapsCount(int32 LapsCount)
{
	GameInstance->SetLapsCount(LapsCount);
}

void UPraktykiMenuUI::SetGameModeType(EGameModeType GameModeType)
{
	GameInstance->SetGameModeType(GameModeType);
}
