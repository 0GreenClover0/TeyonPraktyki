// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PraktykiPlayerController.generated.h"

class APraktykiVehiclePawn;
class UInputMappingContext;
class UPraktykiVehicleUI;

/**
 *  Handles input mapping and user interface.
 */
UCLASS(Abstract)
class PRAKTYKI_API APraktykiPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	TObjectPtr<APraktykiVehiclePawn> VehiclePawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UPraktykiVehicleUI> VehicleUIClass;

	TObjectPtr<UPraktykiVehicleUI> VehicleUI;
};
