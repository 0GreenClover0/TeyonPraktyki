// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PraktykiLapInfo.generated.h"

USTRUCT(BlueprintType)
struct FPraktykiLapInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Lap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LapTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeDelta;

	FPraktykiLapInfo()
	{
		Lap = 0;
		LapTime = 0.0f;
		TimeDelta = 0.0f;
	}

	FPraktykiLapInfo(int32 LapNum, float Time, float Delta)
	{
		Lap = LapNum;
		LapTime = Time;
		TimeDelta = Delta;
	}
};
