// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TornadoActor.generated.h"

UCLASS()
class TORNADO_API ATornadoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATornadoActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FVector CalculateTornadoForcePlayer(FVector TornadoOrigin, FVector ObjectLocation, FVector ObjectVelocity, float ObjectMass);
};
