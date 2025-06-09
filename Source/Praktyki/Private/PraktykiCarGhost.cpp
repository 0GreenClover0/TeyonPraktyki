// Copyright 2025 Teyon. All Rights Reserved.

#include "PraktykiCarGhost.h"

APraktykiCarGhost::APraktykiCarGhost()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APraktykiCarGhost::BeginPlay()
{
	Super::BeginPlay();
}

void APraktykiCarGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentFramesInfo.Num() < 2 || CurrentFrame >= CurrentFramesInfo.Num() - 1)
		return;

	CurrentTime += DeltaTime;

	// Advance frame index if needed
	while (CurrentFrame < CurrentFramesInfo.Num() - 2 && CurrentTime > CurrentFramesInfo[CurrentFrame + 1].Time)
	{
		CurrentFrame++;
	}

	const FFrameInfo& FrameA = CurrentFramesInfo[CurrentFrame];
	const FFrameInfo& FrameB = CurrentFramesInfo[CurrentFrame + 1];

	// Calculate current alpha between frames
	float SegmentDuration = FrameB.Time - FrameA.Time;
	float Alpha = (CurrentTime - FrameA.Time) / SegmentDuration;
	Alpha = FMath::Clamp(Alpha, 0.0f, 1.0f);

	// Interpolate position
	FVector InterpolatedLocation = FMath::Lerp(FrameA.Location, FrameB.Location, Alpha);

	// Interpolate rotation using quaternions
	FQuat QuatA = FrameA.Rotation.Quaternion();
	FQuat QuatB = FrameB.Rotation.Quaternion();
	FQuat InterpolatedQuat = FQuat::Slerp(QuatA, QuatB, Alpha);
	FRotator InterpolatedRotation = InterpolatedQuat.Rotator();

	SetActorLocation(InterpolatedLocation);
	SetActorRotation(InterpolatedRotation);
}

void APraktykiCarGhost::StartGhost(const TArray<FFrameInfo>& FramesInfo)
{
	CurrentFramesInfo = FramesInfo;
}
