// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiComeBackWidget.h"

#include "PraktykiVehiclePawn.h"

void UPraktykiComeBackWidget::UpdateTimeLeft(float Time)
{
	OnTimeLeftUpdate(Time);
}

void UPraktykiComeBackWidget::NativeConstruct()
{
	Super::NativeConstruct();

	VehiclePawn = CastChecked<APraktykiVehiclePawn>(GetOwningPlayerPawn());
}
