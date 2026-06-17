// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterGlide.h"

// Sets default values
ACharacterGlide::ACharacterGlide()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterGlide::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterGlide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterGlide::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterGlide::Glide(FVector ForwardVector, FVector UpVector, float DeltaTime)
{
	UCharacterMovementComponent *CMC = GetCharacterMovement();

	// Adjusting velocity to current direction
	FVector Velocity = GetVelocity();
	float ForwardMagnitude = FVector::DotProduct(Velocity, ForwardVector);
	ForwardMagnitude = FMath::Max(ForwardMagnitude, 0.0f);
	FVector V_forward = ForwardVector * ForwardMagnitude;

	// Damping for upward component
	FVector V_nonforward = Velocity - V_forward;
	float UpwardMagnitude = FVector::DotProduct(V_nonforward, UpVector);
	FVector V_up = UpVector * UpwardMagnitude;
	FVector V_upscaled = V_up;
	if (UpwardMagnitude < 0.0) {
		const float UpHalfLife = 0.01;
		V_upscaled = V_up * FMath::Pow(0.5, DeltaTime / UpHalfLife);
	}

	// Damping for non forward non up (side) component
	FVector V_side = V_nonforward - V_up;
	const float SideHalfLife = 0.5;
	FVector V_sidescaled = V_side * FMath::Pow(0.5, DeltaTime / SideHalfLife);

	CMC->Velocity = V_forward + V_upscaled + V_sidescaled;


	// "Disable" gravity for custom glider calculation
	CMC->AddForce(FVector(0, 0, -CMC->GetGravityZ() * CMC->Mass));

	// Glide calculations
	const double MaxLift = 430;
	FVector GravityVector = FVector(0, 0, CMC->GetGravityZ());
	double DownforceMagnitude = FVector::DotProduct(UpVector, GravityVector);
	FVector EffectiveLiftVector = UpVector * FMath::Min(DownforceMagnitude - MaxLift, 0.0);
	double ThrustMagnitude = FVector::DotProduct(ForwardVector, GravityVector);
	FVector ThrustVector = ForwardVector * ThrustMagnitude;

	FVector ResultantForce = EffectiveLiftVector + ThrustVector;
	CMC->AddForce(ResultantForce * CMC->Mass);
	
}
