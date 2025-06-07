// Copyright 2025 Teyon. All Rights Reserved.


#include "PraktykiVehicleWheelFront.h"

UPraktykiVehicleWheelFront::UPraktykiVehicleWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}
