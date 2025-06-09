// Copyright 2025 Teyon. All Rights Reserved.


#include "PraktykiPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "PraktykiEndRaceWidget.h"
#include "PraktykiGameInstance.h"
#include "PraktykiVehiclePawn.h"
#include "PraktykiVehicleUI.h"
#include "Praktyki/PraktykiGameModeBase.h"

void APraktykiPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(VehicleUI) && IsValid(VehiclePawn))
	{
		VehicleUI->UpdateSpeed(VehiclePawn->GetChaosVehicleMovement()->GetForwardSpeed());

		VehicleUI->UpdateCurrentLapTime(VehiclePawn->GetCurrentLapTime());

		VehicleUI->UpdateOverallTime(VehiclePawn->GetOverallLapsTime());
	}

	if (IsValid(VehicleUI) && IsValid(GameMode))
	{
		VehicleUI->UpdateMaxGameTime(GameMode->GetTime());
	}
}

void APraktykiPlayerController::AbortRace()
{
	OnRaceFinished();
}

void APraktykiPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<APraktykiGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	GameMode->FOnRaceFinishedDelegate.AddDynamic(this, &APraktykiPlayerController::OnRaceFinished);

	GameInstance = GetGameInstance<UPraktykiGameInstance>();

	check(GameInstance);

	// Spawn the UI widget and add it to the viewport.
	VehicleUI = CreateWidget<UPraktykiVehicleUI>(this, VehicleUIClass);

	check(VehicleUI);

	VehicleUI->AddToViewport();

	check(GameInstance);

	VehicleUI->UpdateMaxGameTime(GameInstance->GetMaxGameTime());

	VehicleUI->UpdateRequiredLaps(GameInstance->GetMaxLapsCount());

	VehicleUI->UpdateMode(GameInstance->GetGameModeType());

	LapsInfo.Reserve(GameInstance->GetMaxLapsCount());
}

void APraktykiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!InputSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find an Enhanced Input Subsystem!"));
		return;
	}

	InputSubsystem->AddMappingContext(InputMappingContext, 0);
}

void APraktykiPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	VehiclePawn = CastChecked<APraktykiVehiclePawn>(InPawn);

	VehiclePawn->FOnLapFinishedDelegate.AddDynamic(this, &APraktykiPlayerController::OnLapFinished);
}

void APraktykiPlayerController::OnLapFinished(int32 CurrentLap, float PreviousLapTime)
{
	FPraktykiLapInfo LapInfo = FPraktykiLapInfo(CurrentLap - 1, VehiclePawn->GetLastLapTime(), PreviousLapTime - VehiclePawn->GetLastLapTime());

	if (IsValid(VehicleUI))
	{
		VehicleUI->UpdateCurrentLap(CurrentLap);

		check(VehiclePawn);

		VehicleUI->UpdateBestLapTime(VehiclePawn->GetBestLapTime());

		VehicleUI->UpdateLastLapTime(VehiclePawn->GetLastLapTime());

		VehicleUI->UpdateLapsTable(LapInfo.Lap, LapInfo.LapTime, LapInfo.TimeDelta);
	}

	LapsInfo.Add(LapInfo);

	if (GameInstance->GetMaxLapsCount() == CurrentLap)
	{
		OnRaceFinished();
	}
}

void APraktykiPlayerController::OnRaceFinished()
{
	if (VehicleUI)
	{
		VehicleUI->RemoveFromParent();
	}

	check(VehiclePawn);

	VehiclePawn->SetActorTickEnabled(false);
	VehiclePawn->DetachFromControllerPendingDestroy();

	// Spawn the End Race Widget and add it to the viewport.
	EndRaceWidget = CreateWidget<UPraktykiEndRaceWidget>(this, EndRaceWidgetClass);

	check(EndRaceWidget);

	EndRaceWidget->AddToViewport();

	EndRaceWidget->UpdateBestLapTime(VehiclePawn->GetBestLapTime());
	EndRaceWidget->UpdateOverallTime(VehiclePawn->GetOverallLapsTime());

	EndRaceWidget->UpdateLapsCount(GameInstance->GetMaxLapsCount());

	EndRaceWidget->UpdateLapInfoTable(LapsInfo);

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}
