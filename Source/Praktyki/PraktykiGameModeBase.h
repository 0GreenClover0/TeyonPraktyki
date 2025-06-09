// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PraktykiGameModeBase.generated.h"

class UPraktykiGameInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRaceFinished);

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

public:
	UPROPERTY(BlueprintAssignable)
	FOnRaceFinished FOnRaceFinishedDelegate;

private:
	UPROPERTY()
	UPraktykiGameInstance* GameInstance = nullptr;

	float GameTime = 0.0f;
	bool bGameEnded = false;
};
