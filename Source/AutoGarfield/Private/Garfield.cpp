// Fill out your copyright notice in the Description page of Project Settings.


#include "Garfield.h"

#include "AutoGarfield/PhysicsUtils.h"
#include "Engine/World.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

void AGarfield::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CurrentNearestLasagna = GetNearestLasagna();
	if (CurrentNearestLasagna)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Lasagna exists");
		SeekForce = PhysicsUtils::Seek(this, CurrentNearestLasagna->GetActorLocation(), FloatingMovementComponent);
		SeekForce.Z = 0.0f;
		GetMovementComponent()->AddInputVector(SeekForce);
	}
	
	if (FloatingMovementComponent->Velocity.Y > 0)
	{
		GetCapsuleComponent()->SetRelativeScale3D(FVector(1, 1, 1));
	} else if (FloatingMovementComponent->Velocity.Y < 0)
	{
		GetCapsuleComponent()->SetRelativeScale3D(FVector(1, -1, 1));
	}
}

void AGarfield::BeginPlay()
{
	Super::BeginPlay();
	LasagnaClass = ALasagna::StaticClass();
}

AGarfield::AGarfield() : SeekForce()
{
	PrimaryActorTick.bCanEverTick = true;
	
	FloatingMovementComponent = CreateDefaultSubobject<UPawnMovementComponent, UFloatingPawnMovement>(FName("FloatingMovementComponent"));
	ALasagna::TotalNumberSpawned = 0;
	ALasagna::NumberEaten = 0;
}

ALasagna* AGarfield::GetNearestLasagna() const
{
	// Initialize an array which will contain all Lasagnas on the terrain
	TArray<AActor*> AllLasagnas;
	// Fill it will the actual lasagnas on the terrain
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), LasagnaClass, AllLasagnas);
	if (AllLasagnas.Num() == 0)
	{
		return nullptr;
	}
	// This will serve to obtain the object at the end
	int CurrentNearestLasagnaIndex = 0;
	// The lowest distance for this time, by default the highest number possible for double
	double CurrentNearestLasagnaDistance = std::numeric_limits<double>::max();
	
	UE_LOG(LogTemp, Display, TEXT("Lasagna number = %d"), AllLasagnas.Num());
	
	// Check every Lasagna on the terrain (min algorithm)
	for (int i = 0; i < AllLasagnas.Num(); i++)
	{
		UE_LOG(LogTemp, Display, TEXT("Lasagna index (i) = %d"), i);
		// Get the relative distance
		if (double const CurrentLasagnaDistance = AllLasagnas[i]->GetActorLocation().Z - this->GetActorLocation().Z;
			// Check if it's lower than the previous "lowest" we got
			CurrentLasagnaDistance < CurrentNearestLasagnaDistance
			// We also need to check if the lasagna is high enough (otherwise it is not catchable)
			&& CurrentLasagnaDistance > -50)
		{
			// This is the "new best"
			CurrentNearestLasagnaDistance = CurrentLasagnaDistance;
			// Save the index of the new best
			CurrentNearestLasagnaIndex = i;
			
		}
		UE_LOG(LogTemp, Display, TEXT("Nearest lasagna index = %d"), CurrentNearestLasagnaIndex);
	}
	// Using the index to return the correct instance
	return reinterpret_cast<ALasagna*>(AllLasagnas[CurrentNearestLasagnaIndex]);
}
