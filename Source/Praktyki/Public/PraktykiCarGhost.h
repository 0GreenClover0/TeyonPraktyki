// Copyright 2025 Teyon. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PraktykiCarGhost.generated.h"

struct FFrameInfo
{
	FRotator Rotation;
	FVector Location;
	float Time;
};

UCLASS()
class PRAKTYKI_API APraktykiCarGhost : public AActor
{
	GENERATED_BODY()

public:
	APraktykiCarGhost();

	virtual void Tick(float DeltaTime) override;

	void StartGhost(const TArray<FFrameInfo>& FramesInfo);

protected:
	virtual void BeginPlay() override;

private:
	TArray<FFrameInfo> CurrentFramesInfo;
	float CurrentTime = 0.0f;
	int32 CurrentFrame = 0;
};
