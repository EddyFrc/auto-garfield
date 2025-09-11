// Fill out your copyright notice in the Description page of Project Settings.


#include "Jon.h"

#include "Lasagna.h"

void AJon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// Call Seek
	// Apply force using the resulting vector
	// Check if colliding with point or near it
	// If colliding, call OnControlPointReached
}

void AJon::OnControlPointReached()
{
	// Generate new lasagna for Garfield to eat
	GetWorld()->SpawnActor<ALasagna>(ALasagna::StaticClass(), this->GetActorLocation(), this->GetActorRotation());
	// Delete old point
	// Create new random point
}


void AJon::BeginPlay()
{
	OnControlPointReached();
}
