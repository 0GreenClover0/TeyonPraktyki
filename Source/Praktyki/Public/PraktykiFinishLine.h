// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PraktykiFinishLine.generated.h"

class UBoxComponent;

UCLASS()
class PRAKTYKI_API APraktykiFinishLine : public AActor
{
	GENERATED_BODY()

public:
	APraktykiFinishLine();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnFinishLapTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* FinishLapTrigger;
};
