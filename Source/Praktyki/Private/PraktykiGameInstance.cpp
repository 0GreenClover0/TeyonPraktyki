// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiGameInstance.h"

UPraktykiGameInstance::UPraktykiGameInstance()
{
	MaxGameTimeDefault = MaxGameTime;
	LapsCountDefault = LapsCount;
	GameModeTypeDefault = GameModeType;
}

void UPraktykiGameInstance::SetMaxGameTime(float Time)
{
	MaxGameTime = Time;
}

void UPraktykiGameInstance::SetLapsCount(int32 Count)
{
	LapsCount = Count;
	MaxLapsCount = Count;
}

void UPraktykiGameInstance::SetGameModeType(EGameModeType ModeType)
{
	GameModeType = ModeType;
}

int32 UPraktykiGameInstance::GetMaxLapsCount() const
{
	if (GameModeType == EGameModeType::Training)
	{
		return 1;
	}

	return MaxLapsCount;
}

void UPraktykiGameInstance::ResetToDefault()
{
	MaxGameTime = MaxGameTimeDefault;
	LapsCount = LapsCountDefault;
	GameModeType = GameModeTypeDefault;
}
