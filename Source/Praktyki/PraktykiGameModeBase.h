// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PraktykiGameModeBase.generated.h"

class UPraktykiGameInstance;

/**
 * Base class for other game modes.
 */
UCLASS(MinimalAPI)
class APraktykiGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APraktykiGameModeBase();

	virtual void Tick(float DeltaTime) override;

	float GetTime() const { return GameTime; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UPraktykiGameInstance* GameInstance = nullptr;

	float GameTime = 0.0f;
};
