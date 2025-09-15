#pragma once

class PhysicsUtils
{
	PhysicsUtils();
public:

	static FVector Seek(const AActor* CurrentActor, const FVector& Target, const UPawnMovementComponent* MovementComponent);
	
};
