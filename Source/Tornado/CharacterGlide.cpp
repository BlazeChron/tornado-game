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

