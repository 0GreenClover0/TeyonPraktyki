// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PraktykiVehicleUI.generated.h"

/**
 *  Simple Vehicle UI, displays current speed.
 */
UCLASS(Abstract)
class PRAKTYKI_API UPraktykiVehicleUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// Updates speed on display
	void UpdateSpeed(float NewSpeed);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnSpeedUpdate(float NewSpeed);
};
