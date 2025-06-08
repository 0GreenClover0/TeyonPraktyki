// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiGameInstance.h"

void UPraktykiGameInstance::SetMaxGameTime(float Time)
{
	MaxGameTime = Time;
}

void UPraktykiGameInstance::SetLapsCount(int32 Count)
{
	LapsCount = Count;
}

void UPraktykiGameInstance::SetGameModeType(EGameModeType ModeType)
{
	GameModeType = ModeType;
}
