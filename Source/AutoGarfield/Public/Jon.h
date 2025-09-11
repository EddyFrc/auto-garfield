// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lasagna.h"
#include "PaperCharacter.h"
#include "src/Core/Matrix.h"
#include "Jon.generated.h"

/**
 * 
 */
UCLASS()
class AUTOGARFIELD_API AJon : public APaperCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
    TSubclassOf<ALasagna> LasagnaToSpawn;

	FVector CurrentTarget;
	FVector CurrentForce;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void OnControlPointReached();

	FVector Seek(const FVector& Target);
	
};
