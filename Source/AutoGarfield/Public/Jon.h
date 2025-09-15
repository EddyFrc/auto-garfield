// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lasagna.h"
#include "PaperCharacter.h"
#include "Jon.generated.h"

/**
 * 
 */
UCLASS()
class AUTOGARFIELD_API AJon : public APaperCharacter
{
	GENERATED_BODY()

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* FloatingMovementComponent;

public:

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<ALasagna> LasagnaToSpawn;

	FVector CurrentTarget;
	FVector CurrentForce;

protected:
	virtual void BeginPlay() override;
	
	void OnControlPointReached();

public:
	virtual void Tick(const float DeltaSeconds) override;
	AJon();
};
