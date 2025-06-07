// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiVehicleUI.h"

void UPraktykiVehicleUI::UpdateSpeed(float NewSpeed)
{
	float FormattedSpeed = FMath::Abs(NewSpeed) * 0.036f;

	OnSpeedUpdate(FormattedSpeed);
}
