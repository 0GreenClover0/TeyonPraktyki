// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "PraktykiVehiclePawn.generated.h"

class APraktykiPlayerController;
struct FInputActionValue;
class UCameraComponent;
class UChaosWheeledVehicleMovementComponent;
class UInputAction;
class UPraktykiComeBackWidget;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLapFinished, int32, NewLap, float, PreviousLapTime);

/**
 *  Handles common functionality for all vehicle types, including input
 *  handling, camera management and counting lap times.
 *
 *  Specific vehicle configurations are handled in subclasses.
 */
UCLASS(Abstract)
class PRAKTYKI_API APraktykiVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	APraktykiVehiclePawn();

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void Tick(float DeltaTime) override;

	void FinishLap();

	USpringArmComponent* GetFrontSpringArm() const { return FrontSpringArm; }
	UCameraComponent* GetFollowCamera() const { return FrontCamera; }
	USpringArmComponent* GetBackSpringArm() const { return BackSpringArm; }
	UCameraComponent* GetBackCamera() const { return BackCamera; }

	const TObjectPtr<UChaosWheeledVehicleMovementComponent>& GetChaosVehicleMovement() const { return ChaosVehicleMovement; }

	int32 GetLapCounter() const { return LapsCounter; }
	float GetCurrentLapTime() const { return CurrentLapTime; }
	float GetLastLapTime() const { return LastLapTime; }
	float GetOverallLapsTime() const { return OverallLapsTime; }
	float GetBestLapTime() const { return BestLapTime; }

protected:
	virtual void BeginPlay() override;

	void Steering(const FInputActionValue& Value);

	void Throttle(const FInputActionValue& Value);

	void Brake(const FInputActionValue& Value);

	void StartBrake(const FInputActionValue& Value);
	void StopBrake(const FInputActionValue& Value);

	void StartHandbrake(const FInputActionValue& Value);
	void StopHandbrake(const FInputActionValue& Value);

	void LookAround(const FInputActionValue& Value);

	void ToggleCamera(const FInputActionValue& Value);

	void ResetVehicle(const FInputActionValue& Value);

private:
	void AdjustAngularDamping() const;
	void RealignCamera(float DeltaTime) const;
	void TickCounters(float DeltaTime);
	void CheckGround();

public:
	UPROPERTY(BlueprintAssignable)
	FOnLapFinished FOnLapFinishedDelegate;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input)
	UInputAction* SteeringAction;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input)
	UInputAction* ThrottleAction;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input)
	UInputAction* BrakeAction;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input)
	UInputAction* HandbrakeAction;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input)
	UInputAction* LookAroundAction;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input)
	UInputAction* ToggleCameraAction;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = Input)
	UInputAction* ResetVehicleAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UPraktykiComeBackWidget> ComeBackWidgetClass;

	UPROPERTY()
	TObjectPtr<UPraktykiComeBackWidget> ComeBackWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float OffTrackMaxTime = 5.0f;

	bool bFrontCameraActive = false;

private:
	// Spring Arm for the front camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* FrontSpringArm;

	// Front Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FrontCamera;

	// Spring Arm for the back camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* BackSpringArm;

	// Back Camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* BackCamera;

	UPROPERTY()
	TObjectPtr<UChaosWheeledVehicleMovementComponent> ChaosVehicleMovement;

	UPROPERTY()
	TObjectPtr<APraktykiPlayerController> PlayerController;

	FTimerHandle CheckGroundTimer;

	int32 LapsCounter = 0;
	float CurrentLapTime = 0.0f;
	float LastLapTime = 0.0f;
	float BestLapTime = 0.0f;
	float OverallLapsTime = 0.0f;

	static constexpr float FinishLapCooldown = 7.0f;
	float FinishLapCooldownCounter = 0.0f;

	float OffTrackCounter = 0.0f;
	bool bIsOnTrack = true;
	bool bHasAbortedRace = false;
};
