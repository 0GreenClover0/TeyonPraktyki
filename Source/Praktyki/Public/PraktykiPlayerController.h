// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PraktykiPlayerController.generated.h"

class APraktykiGameModeBase;
class APraktykiVehiclePawn;
class UInputMappingContext;
class UPraktykiEndRaceWidget;
class UPraktykiGameInstance;
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

	void AbortRace();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void OnLapFinished(int32 CurrentLap);

	UFUNCTION()
	void OnRaceFinished();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY()
	TObjectPtr<APraktykiVehiclePawn> VehiclePawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UPraktykiVehicleUI> VehicleUIClass;

	UPROPERTY()
	TObjectPtr<UPraktykiVehicleUI> VehicleUI;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UPraktykiEndRaceWidget> EndRaceWidgetClass;

	UPROPERTY()
	TObjectPtr<UPraktykiEndRaceWidget> EndRaceWidget;

	UPROPERTY()
	TObjectPtr<APraktykiGameModeBase> GameMode;

	UPROPERTY()
	TObjectPtr<UPraktykiGameInstance> GameInstance;
};
