// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PraktykiMenuGameMode.generated.h"

class UPraktykiMenuUI;

/**
 * Menu game mode.
 */
UCLASS()
class PRAKTYKI_API APraktykiMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
	TSubclassOf<UPraktykiMenuUI> PraktykiMenuWidgetClass;

private:
	UPROPERTY()
	UPraktykiMenuUI* PraktykiMenuUI;
};
