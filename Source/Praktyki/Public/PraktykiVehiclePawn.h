// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "PraktykiVehiclePawn.generated.h"

struct FInputActionValue;
class UCameraComponent;
class UChaosWheeledVehicleMovementComponent;
class UInputAction;
class USpringArmComponent;

/**
 *  Handles common functionality for all vehicle types,
 *  including input handling and camera management.
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

    USpringArmComponent* GetFrontSpringArm() const { return FrontSpringArm; }
    UCameraComponent* GetFollowCamera() const { return FrontCamera; }
    USpringArmComponent* GetBackSpringArm() const { return BackSpringArm; }
    UCameraComponent* GetBackCamera() const { return BackCamera; }
    const TObjectPtr<UChaosWheeledVehicleMovementComponent>& GetChaosVehicleMovement() const { return ChaosVehicleMovement; }

protected:
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

    /** Called when the brake lights are turned on or off */
    UFUNCTION(BlueprintImplementableEvent, Category = "Vehicle")
    void BrakeLights(bool bBraking);

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

    bool bFrontCameraActive = false; // TODO: Change to enum class

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

    TObjectPtr<UChaosWheeledVehicleMovementComponent> ChaosVehicleMovement;
};
