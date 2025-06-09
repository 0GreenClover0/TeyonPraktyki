// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiEndRaceWidget.h"

void UPraktykiEndRaceWidget::UpdateBestLapTime(float BestLapTime)
{
	OnBestLapTimeUpdate(BestLapTime);
}

void UPraktykiEndRaceWidget::UpdateOverallTime(float OverallTime)
{
	OnOverallTimeUpdate(OverallTime);
}

void UPraktykiEndRaceWidget::UpdateLapsCount(int32 LapsCount)
{
	OnLapsCountUpdate(LapsCount);
}

FString UPraktykiEndRaceWidget::FormatTime(float TimeInSeconds)
{
	int32 Minutes = FMath::FloorToInt(TimeInSeconds / 60.0f);
	int32 Seconds = FMath::FloorToInt(FMath::Fmod(TimeInSeconds, 60.0f));
	int32 Milliseconds = FMath::RoundToInt(FMath::Fmod(TimeInSeconds, 1.0f) * 1000.0f);

	return FString::Printf(TEXT("%d:%02d.%03d"), Minutes, Seconds, Milliseconds);
}
