// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameModeType.h"
#include "PraktykiMenuUI.generated.h"

class UPraktykiGameInstance;

/**
 * UI for game settings.
 */
UCLASS()
class PRAKTYKI_API UPraktykiMenuUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetMaxTime(float Time);

	UFUNCTION(BlueprintCallable)
	void SetLapsCount(int32 LapsCount);

	UFUNCTION(BlueprintCallable)
	void SetGameModeType(EGameModeType GameModeType);

private:
	UPROPERTY(VisibleAnywhere)
	UPraktykiGameInstance* GameInstance;
};
