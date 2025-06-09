// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PraktykiComeBackWidget.generated.h"

class APraktykiVehiclePawn;

/**
 * Widget displaying the information to come back on track.
 */
UCLASS()
class PRAKTYKI_API UPraktykiComeBackWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateTimeLeft(float Time);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnTimeLeftUpdate(float Time);

protected:
	UPROPERTY()
	TObjectPtr<APraktykiVehiclePawn> VehiclePawn;
};
