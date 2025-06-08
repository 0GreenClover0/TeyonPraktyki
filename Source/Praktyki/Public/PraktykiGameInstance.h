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
	void SetMaxGameTime(float Time);
	float GetMaxGameTime() const { return MaxGameTime; }
	void SetLapsCount(int32 Count);
	int32 GetLapsCount() const { return LapsCount; }
	void SetGameModeType(EGameModeType ModeType);
	EGameModeType GetGameModeType() const { return GameModeType; }

private:
	float MaxGameTime = 0.0f;
	int32 LapsCount = 1;
	EGameModeType GameModeType = EGameModeType::Training;
};
