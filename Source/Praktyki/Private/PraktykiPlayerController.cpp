// Copyright 2025 Teyon. All Rights Reserved.


#include "PraktykiPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PraktykiGameInstance.h"
#include "PraktykiVehiclePawn.h"
#include "PraktykiVehicleUI.h"
#include "Kismet/GameplayStatics.h"
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

void APraktykiPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<APraktykiGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	// Spawn the UI widget and add it to the viewport.
	VehicleUI = CreateWidget<UPraktykiVehicleUI>(this, VehicleUIClass);

	check(VehicleUI);

	VehicleUI->AddToViewport();

	UPraktykiGameInstance* GameInstance = GetGameInstance<UPraktykiGameInstance>();

	check(GameInstance);

	VehicleUI->UpdateMaxGameTime(GameInstance->GetMaxGameTime());

	VehicleUI->UpdateRequiredLaps(GameInstance->GetLapsCount());

	VehicleUI->UpdateMode(GameInstance->GetGameModeType());
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

void APraktykiPlayerController::OnLapFinished(int32 CurrentLap)
{
	if (IsValid(VehicleUI))
	{
		VehicleUI->UpdateCurrentLap(CurrentLap);

		check(VehiclePawn);

		VehicleUI->UpdateBestLapTime(VehiclePawn->GetBestLapTime());

		VehicleUI->UpdateLastLapTime(VehiclePawn->GetLastLapTime());
	}
}
