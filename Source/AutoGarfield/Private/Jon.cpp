// Fill out your copyright notice in the Description page of Project Settings.


#include "Jon.h"

#include "Components/CapsuleComponent.h"

void AJon::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // Call Seek
    CurrentForce = Seek(CurrentTarget);
    // Apply force using the resulting vector
    this->GetCapsuleComponent()->AddForce(CurrentForce, NAME_None, true);
    // Check if near the defined target
    if (FMath::Abs(this->GetActorLocation().Y - CurrentTarget.Y) < 5)
    {
    	UE_LOGFMT(LogTemp, Display, "Control Point Reached with distance = `{Distance}`", this->GetActorLocation().Y - CurrentTarget.Y);
        // If near the target, call OnControlPointReached
        OnControlPointReached();
    }

}

void AJon::OnControlPointReached()
{
	UE_LOG(LogTemp, Display, TEXT("OnControlPointReached"));
	// Generate new lasagna for Garfield to eat
	GetWorld()->SpawnActor<ALasagna>(LasagnaToSpawn, this->GetActorLocation(), this->GetActorRotation());
	// Create new random point
	CurrentTarget = FVector(this->GetActorLocation().X, FMath::RandRange(-300, 300), this->GetActorLocation().Z);
}


void AJon::BeginPlay()
{
	UE_LOG(LogTemp, Display, TEXT("BeginPlay"));
	Super::BeginPlay();

	OnControlPointReached();


}

FVector AJon::Seek(const FVector& Target)
{
	FVector Desired = Target - this->GetActorLocation();
	Desired.Normalize();
	Desired *= Speed;
	FVector Steering = Desired - this->GetVelocity();
	Steering = Steering.GetClampedToMaxSize(Speed);
	return Steering;
}

AJon::AJon()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}
