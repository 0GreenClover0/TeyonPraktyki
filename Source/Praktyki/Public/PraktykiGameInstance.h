// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameModeType.h"
#include "PraktykiGameInstance.generated.h"

UCLASS()
class PRAKTYKI_API UPraktykiGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPraktykiGameInstance();

	void SetMaxGameTime(float Time);

	UFUNCTION(BlueprintCallable)
	float GetMaxGameTime() const { return MaxGameTime; }

	void SetLapsCount(int32 Count);

	UFUNCTION(BlueprintCallable)
	int32 GetLapsCount() const { return LapsCount; }

	void SetGameModeType(EGameModeType ModeType);

	UFUNCTION(BlueprintCallable)
	EGameModeType GetGameModeType() const { return GameModeType; }

	int32 GetMaxLapsCount() const;

	UFUNCTION(BlueprintCallable)
	void ResetToDefault();

private:
	float MaxGameTime = 30.0f;
	int32 LapsCount = 1;
	int32 MaxLapsCount = 1;
	EGameModeType GameModeType = EGameModeType::Training;

	float MaxGameTimeDefault;
	int32 LapsCountDefault;
	EGameModeType GameModeTypeDefault;
};
