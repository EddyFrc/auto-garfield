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

public:

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<ALasagna> LasagnaToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Variables")
	double Speed = 3000;

	FVector CurrentTarget;
	FVector CurrentForce;

protected:
	virtual void BeginPlay() override;
	
	void OnControlPointReached();

	FVector Seek(const FVector& Target);

public:
	virtual void Tick(float DeltaSeconds) override;
	AJon();
};
