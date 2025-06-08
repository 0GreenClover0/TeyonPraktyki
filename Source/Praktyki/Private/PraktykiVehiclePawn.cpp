// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiVehiclePawn.h"

#include "Camera/CameraComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"

APraktykiVehiclePawn::APraktykiVehiclePawn()
{
	// Construct back camera boom
	BackSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Back Spring Arm"));
	BackSpringArm->SetupAttachment(GetMesh());
	BackSpringArm->TargetArmLength = 650.0f;
	BackSpringArm->SocketOffset.Z = 150.0f;
	BackSpringArm->bDoCollisionTest = false;
	BackSpringArm->bInheritPitch = false;
	BackSpringArm->bInheritRoll = false;
	BackSpringArm->bEnableCameraRotationLag = true;
	BackSpringArm->CameraRotationLagSpeed = 2.0f;
	BackSpringArm->CameraLagMaxDistance = 50.0f;

	BackCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Back Camera"));
	BackCamera->SetupAttachment(BackSpringArm);

	// Construct front camera boom
	FrontSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Front Spring Arm"));
	FrontSpringArm->SetupAttachment(GetMesh());
	FrontSpringArm->TargetArmLength = 0.0f;
	FrontSpringArm->bDoCollisionTest = false;
	FrontSpringArm->bEnableCameraRotationLag = true;
	FrontSpringArm->CameraRotationLagSpeed = 15.0f;
	FrontSpringArm->SetRelativeLocation(FVector(30.0f, 0.0f, 120.0f));

	FrontCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Front Camera"));
	FrontCamera->SetupAttachment(FrontSpringArm);
	FrontCamera->bAutoActivate = true;

	// Configure the car mesh
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName(FName("Vehicle"));

	ChaosVehicleMovement = CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());
}

void APraktykiVehiclePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to find an Enhanced Input component!"));
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("Test!"));

	// Steering
	EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &APraktykiVehiclePawn::Steering);
	EnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &APraktykiVehiclePawn::Steering);

	// Throttle
	EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &APraktykiVehiclePawn::Throttle);
	EnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &APraktykiVehiclePawn::Throttle);

	// Break
	EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &APraktykiVehiclePawn::Brake);
	EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Started, this, &APraktykiVehiclePawn::StartBrake);
	EnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &APraktykiVehiclePawn::StopBrake);

	// Handbrake
	EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Started, this, &APraktykiVehiclePawn::StartHandbrake);
	EnhancedInputComponent->BindAction(HandbrakeAction, ETriggerEvent::Completed, this, &APraktykiVehiclePawn::StopHandbrake);

	// Look around
	EnhancedInputComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &APraktykiVehiclePawn::LookAround);

	// Toggle camera
	EnhancedInputComponent->BindAction(ToggleCameraAction, ETriggerEvent::Triggered, this, &APraktykiVehiclePawn::ToggleCamera);

	// Reset the vehicle
	EnhancedInputComponent->BindAction(ResetVehicleAction, ETriggerEvent::Triggered, this, &APraktykiVehiclePawn::ResetVehicle);
}

void APraktykiVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AdjustAngularDamping();

	RealignCamera(DeltaTime);

	TickCounters(DeltaTime);
}

void APraktykiVehiclePawn::FinishLap()
{
	if (FinishLapCooldownCounter > 0.0f)
	{
		return;
	}

	LapsCounter += 1;

	if (BestLapTime > CurrentLapTime)
	{
		BestLapTime = CurrentLapTime;
	}

	LastLapTime = CurrentLapTime;
	CurrentLapTime = 0.0f;

	FinishLapCooldownCounter = FinishLapCooldown;

	FOnLapFinishedDelegate.Broadcast(LapsCounter);
}

void APraktykiVehiclePawn::Steering(const FInputActionValue& Value)
{
	float SteeringValue = Value.Get<float>();

	ChaosVehicleMovement->SetSteeringInput(SteeringValue);
}

void APraktykiVehiclePawn::Throttle(const FInputActionValue& Value)
{
	float ThrottleValue = Value.Get<float>();

	ChaosVehicleMovement->SetThrottleInput(ThrottleValue);
}

void APraktykiVehiclePawn::Brake(const FInputActionValue& Value)
{
	float BreakValue = Value.Get<float>();

	ChaosVehicleMovement->SetBrakeInput(BreakValue);
}

void APraktykiVehiclePawn::StartBrake(const FInputActionValue& Value)
{
}

void APraktykiVehiclePawn::StopBrake(const FInputActionValue& Value)
{
	ChaosVehicleMovement->SetBrakeInput(0.0f);
}

void APraktykiVehiclePawn::StartHandbrake(const FInputActionValue& Value)
{
	ChaosVehicleMovement->SetHandbrakeInput(true);
}

void APraktykiVehiclePawn::StopHandbrake(const FInputActionValue& Value)
{
	ChaosVehicleMovement->SetHandbrakeInput(false);
}

void APraktykiVehiclePawn::LookAround(const FInputActionValue& Value)
{
	float LookValue = Value.Get<float>();

	BackSpringArm->AddLocalRotation(FRotator(0.0f, LookValue, 0.0f));
}

void APraktykiVehiclePawn::ToggleCamera(const FInputActionValue& Value)
{
	bFrontCameraActive = !bFrontCameraActive;

	FrontCamera->SetActive(bFrontCameraActive);
	BackCamera->SetActive(!bFrontCameraActive);
}

void APraktykiVehiclePawn::ResetVehicle(const FInputActionValue& Value)
{
	// Reset to a location slightly above our current one
	FVector ResetLocation = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);

	// Reset to our yaw. Ignore pitch and roll
	FRotator ResetRotation = GetActorRotation();
	ResetRotation.Pitch = 0.0f;
	ResetRotation.Roll = 0.0f;

	// Teleport the actor to the reset spot and reset physics
	SetActorTransform(FTransform(ResetRotation, ResetLocation, FVector::OneVector), false, nullptr, ETeleportType::TeleportPhysics);

	GetMesh()->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);

	UE_LOG(LogTemp, Warning, TEXT("Reset Vehicle"));
}

void APraktykiVehiclePawn::AdjustAngularDamping() const
{
	// Angular damping if the vehicle is in midair
	bool bMovingOnGround = ChaosVehicleMovement->IsMovingOnGround();
	GetMesh()->SetAngularDamping(bMovingOnGround ? 0.0f : 3.0f);
}

void APraktykiVehiclePawn::RealignCamera(float DeltaTime) const
{
	// Realign the camera yaw to face front
	float CameraYaw = BackSpringArm->GetRelativeRotation().Yaw;
	CameraYaw = FMath::FInterpTo(CameraYaw, 0.0f, DeltaTime, 1.0f);

	BackSpringArm->SetRelativeRotation(FRotator(0.0f, CameraYaw, 0.0f));
}

void APraktykiVehiclePawn::TickCounters(float DeltaTime)
{
	CurrentLapTime += DeltaTime;
	OverallLapsTime += DeltaTime;

	FinishLapCooldownCounter -= DeltaTime;

	if (FinishLapCooldownCounter < 0.0f)
	{
		FinishLapCooldownCounter = 0.0f;
	}
}
