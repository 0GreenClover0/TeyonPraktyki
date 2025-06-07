// Copyright 2025 Teyon. All Rights Reserved.


#include "PraktykiPorschePawn.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PraktykiPorscheWheelFront.h"
#include "PraktykiPorscheWheelRear.h"

APraktykiPorschePawn::APraktykiPorschePawn()
{
	// Construct mesh components
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(GetMesh());

	WheelFrontLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Front Left"));
	WheelFrontLeft->SetupAttachment(GetMesh(), FName("wheel_front_left_turn"));
	WheelFrontLeft->SetCollisionProfileName(FName("NoCollision"));

	WheelFrontRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Front Right"));
	WheelFrontRight->SetupAttachment(GetMesh(), FName("wheel_front_right_turn"));
	WheelFrontRight->SetCollisionProfileName(FName("NoCollision"));
	WheelFrontRight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	WheelRearLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Rear Left"));
	WheelRearLeft->SetupAttachment(GetMesh(), FName("wheel_back_left_spin"));
	WheelRearLeft->SetCollisionProfileName(FName("NoCollision"));

	WheelRearRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Rear Right"));
	WheelRearRight->SetupAttachment(GetMesh(), FName("wheel_back_right_spin"));
	WheelRearRight->SetCollisionProfileName(FName("NoCollision"));
	WheelRearRight->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));

	FenderRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fender Right"));
	FenderRight->SetupAttachment(GetMesh(), FName("fender_right"));
	FenderRight->SetCollisionProfileName(FName("NoCollision"));

	FenderLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Fender Left"));
	FenderLeft->SetupAttachment(GetMesh(), FName("fender_left"));
	FenderLeft->SetCollisionProfileName(FName("NoCollision"));

	FrontBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front Bumper"));
	FrontBumper->SetupAttachment(GetMesh(), FName("bumper_front"));
	FrontBumper->SetCollisionProfileName(FName("NoCollision"));

	FrontHood = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Front Hood"));
	FrontHood->SetupAttachment(GetMesh(), FName("hood_front"));
	FrontHood->SetCollisionProfileName(FName("NoCollision"));

	DoorRight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Right"));
	DoorRight->SetupAttachment(GetMesh(), FName("door_right"));
	DoorRight->SetCollisionProfileName(FName("NoCollision"));

	DoorLeft = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Left"));
	DoorLeft->SetupAttachment(GetMesh(), FName("door_left"));
	DoorLeft->SetCollisionProfileName(FName("NoCollision"));

	RearBumper = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rear Bumper"));
	RearBumper->SetupAttachment(GetMesh(), FName("bumper_rear"));
	RearBumper->SetCollisionProfileName(FName("NoCollision"));

	RearBoot = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rear Boot"));
	RearBoot->SetupAttachment(GetMesh(), FName("boot_rear"));
	RearBoot->SetCollisionProfileName(FName("NoCollision"));

	// Adjust the cameras
	GetFrontSpringArm()->SetRelativeLocation(FVector(-5.0f, -30.0f, 135.0f));
	GetBackSpringArm()->SetRelativeLocation(FVector(0.0f, 0.0f, 75.0f));

	// Set up the chassis
	GetChaosVehicleMovement()->ChassisHeight = 160.0f;
	GetChaosVehicleMovement()->DragCoefficient = 0.1f;
	GetChaosVehicleMovement()->DownforceCoefficient = 0.1f;
	GetChaosVehicleMovement()->CenterOfMassOverride = FVector(0.0f, 0.0f, 75.0f);
	GetChaosVehicleMovement()->bEnableCenterOfMassOverride = true;

	// Set up the wheels
	GetChaosVehicleMovement()->bLegacyWheelFrictionPosition = true;
	GetChaosVehicleMovement()->WheelSetups.SetNum(4);

	GetChaosVehicleMovement()->WheelSetups[0].WheelClass = UPraktykiPorscheWheelFront::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[0].BoneName = FName("wheel_front_left_turn");
	GetChaosVehicleMovement()->WheelSetups[0].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[1].WheelClass = UPraktykiPorscheWheelFront::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[1].BoneName = FName("wheel_front_right_turn");
	GetChaosVehicleMovement()->WheelSetups[1].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[2].WheelClass = UPraktykiPorscheWheelRear::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[2].BoneName = FName("wheel_back_left_spin");
	GetChaosVehicleMovement()->WheelSetups[2].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	GetChaosVehicleMovement()->WheelSetups[3].WheelClass = UPraktykiPorscheWheelRear::StaticClass();
	GetChaosVehicleMovement()->WheelSetups[3].BoneName = FName("wheel_back_right_spin");
	GetChaosVehicleMovement()->WheelSetups[3].AdditionalOffset = FVector(0.0f, 0.0f, 0.0f);

	// Set up the engine
	GetChaosVehicleMovement()->EngineSetup.MaxTorque = 750.0f;
	GetChaosVehicleMovement()->EngineSetup.MaxRPM = 7000.0f;
	GetChaosVehicleMovement()->EngineSetup.EngineIdleRPM = 900.0f;
	GetChaosVehicleMovement()->EngineSetup.EngineBrakeEffect = 0.2f;
	GetChaosVehicleMovement()->EngineSetup.EngineRevUpMOI = 5.0f;
	GetChaosVehicleMovement()->EngineSetup.EngineRevDownRate = 600.0f;

	// Set up the differential
	GetChaosVehicleMovement()->DifferentialSetup.DifferentialType = EVehicleDifferential::AllWheelDrive;
	GetChaosVehicleMovement()->DifferentialSetup.FrontRearSplit = 0.5f;

	// Set up the steering
	GetChaosVehicleMovement()->SteeringSetup.SteeringType = ESteeringType::AngleRatio;
	GetChaosVehicleMovement()->SteeringSetup.AngleRatio = 0.7f;
}
