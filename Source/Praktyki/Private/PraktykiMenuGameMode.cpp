// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiMenuGameMode.h"

#include "PraktykiMenuUI.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void APraktykiMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!PlayerController)
	{
		return;
	}

	PlayerController->bShowMouseCursor = true;
	PlayerController->bEnableClickEvents = true;
	PlayerController->bEnableMouseOverEvents = true;

	if (PraktykiMenuWidgetClass)
	{
		PraktykiMenuUI = CreateWidget<UPraktykiMenuUI>(GetWorld(), PraktykiMenuWidgetClass);

		check(PraktykiMenuUI);

		PraktykiMenuUI->AddToViewport();
	}
}
