// Fill out your copyright notice in the Description page of Project Settings.


#include "Jon.h"

#include "Lasagna.h"

void AJon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// Call Seek
	CurrentForce = Seek(CurrentTarget);
	// Apply force using the resulting vector
	LaunchCharacter(CurrentForce, true, true);
	// Check if near the defined target
	if ((this->GetActorLocation() - CurrentTarget).Y < 5)
	{
		// If near the target, call OnControlPointReached
		OnControlPointReached();
	}
}

void AJon::OnControlPointReached()
{
	// Generate new lasagna for Garfield to eat
	GetWorld()->SpawnActor<ALasagna>(LasagnaToSpawn, this->GetActorLocation(), this->GetActorRotation());
	// Create new random point
	CurrentTarget = FVector(this->GetActorLocation().X, FMath::RandRange(-550.0, 550.0), this->GetActorLocation().Z);
}


void AJon::BeginPlay()
{
	OnControlPointReached();
}

FVector AJon::Seek(const FVector& Target)
{
	FVector Desired = Target - this->GetActorLocation();
	Desired.Normalize();
	Desired *= 100.0;
	FVector Steering = Desired - this->GetVelocity();
	Steering = Steering.GetClampedToMaxSize(100.0);
	return Steering;
}
