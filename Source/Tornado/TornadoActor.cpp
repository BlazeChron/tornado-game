// Fill out your copyright notice in the Description page of Project Settings.


#include "TornadoActor.h"

// Sets default values
ATornadoActor::ATornadoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATornadoActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATornadoActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
 * TornadoOrigin: Reference point for the Tornado at the bottom and center of the capsule/cylinder
 * ObjectLocation: World Location of the Object
 */
void CalculateTornadoForcePlayer(FVector TornadoOrigin, FVector ObjectLocation, FVector ObjectVelocity, float ObjectMass) {
	/* 
	 * Calculations for Rankine Vortex Converted to Cartesian Coordinates from Cylindrical coordinates
	 * defined here : https://en.wikipedia.org/wiki/Rankine_vortex
	 * Idea is to use Drag equation at the object's current position
	 */
	
	// Object location wrt TornadoOrigin
	FVector location = ObjectLocation - TornadoOrigin;
	float radius = sqrt(pow(location.X, 2) + pow(location.Y, 2));

	/* Rankine Vortex characteristics:
	 * Angular Velocity w
	 * Inner radius a
	 * V_r = 0
	 * V_theta = wr (inner radius) or w(a^2)/r (outer radius)
	 * V_z = 0
	 */
	const float w = 0.3;

	// TODO add "a"

	float V_theta = w * radius;
	
	// Velocity of particle at Object Location
	// V_u = -r * V_theta * sin(theta) = -r * V_theta y / r
	// V_v =  r * V_theta * sin(theta) =  r * V_theta x / r
	float V_u = -radius * V_theta * location.Y / radius;
	float V_v =  radius * V_theta * location.X / radius;
	// TODO float V_z

	// Drag equation
	// 1/2 p v_rel 
}
