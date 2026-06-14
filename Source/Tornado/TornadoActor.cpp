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
FVector ATornadoActor::CalculateTornadoForcePlayer(FVector TornadoOrigin, FVector ObjectLocation, FVector ObjectVelocity, float ObjectMass) {
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
	// TODO
	float V_z = 1; // Upwards force
	FVector V_point = FVector(V_u, V_v, V_z);

	/* Drag equation
	 * F_d = 1/2 * p * A * c_d * |v_rel|^2 
	 * p Mass density
	 * A Reference area
	 * c_d Drag coefficient, experimentally determined related to the object geometry 
	 * v_rel relative velocity of fluid flow wrt object velocity
	 * 
	 * TODO add the granularity to this equation instead of just C
	 * Simplified formula combining p A c_d as a constant C (lmao)
	 * F_d = C/2 |v_rel|^2
	 * For the vector: C/2 |v_rel| v_rel
	 */ 

	const float C = 0.00001; // Higher = More drag
	FVector v_rel = V_point - ObjectVelocity;
	FVector DragForce = C / 2 * v_rel.Length() * v_rel;

	return DragForce;
}
