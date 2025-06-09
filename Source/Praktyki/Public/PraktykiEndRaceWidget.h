// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PraktykiLapInfo.h"
#include "Blueprint/UserWidget.h"
#include "PraktykiEndRaceWidget.generated.h"

/**
 * Widget that shows results after a race.
 */
UCLASS()
class PRAKTYKI_API UPraktykiEndRaceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateBestLapTime(float BestLapTime);
	void UpdateOverallTime(float OverallTime);
	void UpdateLapsCount(int32 LapsCount);
	void UpdateLapInfoTable(const TArray<FPraktykiLapInfo>& LapsInfo);

protected:
	UFUNCTION(BlueprintCallable)
	FString FormatTime(float TimeInSeconds);

	UFUNCTION(BlueprintImplementableEvent)
	void OnBestLapTimeUpdate(float BestLapTime);

	UFUNCTION(BlueprintImplementableEvent)
	void OnOverallTimeUpdate(float OverallTime);

	UFUNCTION(BlueprintImplementableEvent)
	void OnLapsCountUpdate(int32 LapsCount);

	UFUNCTION(BlueprintImplementableEvent)
	void OnLapInfoTableUpdate(const TArray<FPraktykiLapInfo>& LapsInfo);
};
