// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PraktykiVehicleUI.generated.h"

/**
 *  Vehicle UI, displays current speed, lap times, current time etc.
 */
UCLASS(Abstract)
class PRAKTYKI_API UPraktykiVehicleUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// Updates corresponding attributes on display

	void UpdateSpeed(float NewSpeed);
	void UpdateCurrentLapTime(float CurrentLapTime);
	void UpdateLastLapTime(float LastLapTime);
	void UpdateOverallTime(float CurrentLapTime);
	void UpdateCurrentLap(int32 CurrentLap);
	void UpdateBestLapTime(float BestLapTime);

protected:
	UFUNCTION(BlueprintCallable)
	FString FormatTime(float TimeInSeconds);

	UFUNCTION(BlueprintCallable)
	FString FormatSpeed(float Speed);

	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnSpeedUpdate(float NewSpeed);

	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnCurrentLapTimeUpdate(float CurrentLapTime);

	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnOverallTimeUpdate(float OverallTime);

	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnCurrentLapUpdate(int32 CurrentLap);

	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnBestLapTimeUpdate(float BestLapTime);

	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnLastLapTimeUpdate(float LastLapTime);
};
