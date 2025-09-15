#include "PhysicsUtils.h"

#include "GameFramework/PawnMovementComponent.h"

FVector PhysicsUtils::Seek(const AActor* CurrentActor, const FVector& Target, const UPawnMovementComponent* MovementComponent)
{
	FVector Desired = Target - CurrentActor->GetActorLocation();
	Desired.Normalize();
	Desired *= MovementComponent->GetMaxSpeed();
	FVector Steering = Desired - MovementComponent->Velocity;
	Steering = Steering.GetClampedToMaxSize(MovementComponent->GetMaxSpeed());
	return Steering;
}

PhysicsUtils::PhysicsUtils() {}
