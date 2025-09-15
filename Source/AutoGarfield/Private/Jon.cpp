// Fill out your copyright notice in the Description page of Project Settings.


#include "Jon.h"

#include "AutoGarfield/PhysicsUtils.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"

void AJon::Tick(const float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // Call Seek
	CurrentForce = PhysicsUtils::Seek(this, CurrentTarget, FloatingMovementComponent);
    // Apply force using the resulting vector
	GetMovementComponent()->AddInputVector(CurrentForce);
    // Check if near the defined target
    if (FMath::Abs(this->GetActorLocation().Y - CurrentTarget.Y) < 50)
    {
    	UE_LOGFMT(LogTemp, Display, "Control Point Reached with distance = `{Distance}`", this->GetActorLocation().Y - CurrentTarget.Y);
        // If near the target, call OnControlPointReached
        OnControlPointReached();
    }
	
	if (FloatingMovementComponent->Velocity.Y > 0)
	{
		GetCapsuleComponent()->SetRelativeScale3D(FVector(1, 1, 1));
	} else if (FloatingMovementComponent->Velocity.Y < 0)
	{
		GetCapsuleComponent()->SetRelativeScale3D(FVector(1, -1, 1));
	}
}

void AJon::OnControlPointReached()
{
	UE_LOG(LogTemp, Display, TEXT("OnControlPointReached"));
	// Generate new lasagna for Garfield to eat
	GetWorld()->SpawnActor<ALasagna>(LasagnaToSpawn, this->GetActorLocation(), this->GetActorRotation());
	// Create new random point
	CurrentTarget = FVector(this->GetActorLocation().X, FMath::RandRange(-550, 550), this->GetActorLocation().Z);
}


void AJon::BeginPlay()
{
	UE_LOG(LogTemp, Display, TEXT("BeginPlay"));
	Super::BeginPlay();

	OnControlPointReached();
	
}

AJon::AJon()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	FloatingMovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(FName("FloatingMovementComponent"));
}
