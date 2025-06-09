// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiVehicleUI.h"

void UPraktykiVehicleUI::UpdateMaxGameTime(float MaxGameTime)
{
	OnMaxGameTimeUpdate(MaxGameTime);
}

void UPraktykiVehicleUI::UpdateSpeed(float NewSpeed)
{
	constexpr float KilometersPerHourConverionRate = 0.036f;
	float FormattedSpeed = FMath::Abs(NewSpeed) * KilometersPerHourConverionRate;

	OnSpeedUpdate(FormattedSpeed);
}

void UPraktykiVehicleUI::UpdateCurrentLapTime(float CurrentLapTime)
{
	OnCurrentLapTimeUpdate(CurrentLapTime);
}

void UPraktykiVehicleUI::UpdateLastLapTime(float LastLapTime)
{
	OnLastLapTimeUpdate(LastLapTime);
}

void UPraktykiVehicleUI::UpdateOverallTime(float OverallTime)
{
	OnOverallTimeUpdate(OverallTime);
}

void UPraktykiVehicleUI::UpdateCurrentLap(int32 CurrentLap)
{
	OnCurrentLapUpdate(CurrentLap);
}

void UPraktykiVehicleUI::UpdateRequiredLaps(int32 LapsCount)
{
	OnRequiredLapsUpdate(LapsCount);
}

void UPraktykiVehicleUI::UpdateBestLapTime(float BestLapTime)
{
	OnBestLapTimeUpdate(BestLapTime);
}

void UPraktykiVehicleUI::UpdateMode(EGameModeType GameModeType)
{
	OnGameModeTypeUpdate(GameModeType);
}

void UPraktykiVehicleUI::UpdateLapsTable(int32 Lap, float LapTime, float DeltaBest)
{
	OnLapsTableUpdate(Lap, LapTime, DeltaBest);
}

FString UPraktykiVehicleUI::FormatTime(float TimeInSeconds)
{
	int32 Minutes = FMath::FloorToInt(TimeInSeconds / 60.0f);
	int32 Seconds = FMath::FloorToInt(FMath::Fmod(TimeInSeconds, 60.0f));
	int32 Milliseconds = FMath::RoundToInt(FMath::Fmod(TimeInSeconds, 1.0f) * 1000.0f);

	return FString::Printf(TEXT("%d:%02d.%03d"), Minutes, Seconds, Milliseconds);
}

FString UPraktykiVehicleUI::FormatSpeed(float Speed)
{
	return FString::FromInt(FMath::FloorToInt(Speed));
}
