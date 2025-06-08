// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiFinishLine.h"

#include "Components/BoxComponent.h"
#include "PraktykiVehiclePawn.h"

APraktykiFinishLine::APraktykiFinishLine()
{
	PrimaryActorTick.bCanEverTick = false;

	FinishLapTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Finish Lap Trigger"));
	SetRootComponent(FinishLapTrigger);
}

void APraktykiFinishLine::BeginPlay()
{
	Super::BeginPlay();

	FinishLapTrigger->OnComponentBeginOverlap.AddDynamic(this, &APraktykiFinishLine::OnFinishLapTriggerBeginOverlap);
}

void APraktykiFinishLine::OnFinishLapTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA<APraktykiVehiclePawn>())
	{
		return;
	}

	APraktykiVehiclePawn* VehiclePawn = Cast<APraktykiVehiclePawn>(OtherActor);

	VehiclePawn->FinishLap();
}
