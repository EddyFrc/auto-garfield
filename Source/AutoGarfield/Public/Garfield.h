// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lasagna.h"
#include "PaperCharacter.h"
#include "Garfield.generated.h"

/**
 * 
 */
UCLASS()
class AUTOGARFIELD_API AGarfield : public APaperCharacter
{
	GENERATED_BODY()

	UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPawnMovementComponent* FloatingMovementComponent;

public:

	FVector SeekForce;

	TSubclassOf<ALasagna> LasagnaClass;

	ALasagna* CurrentNearestLasagna;

	ALasagna* GetNearestLasagna() const;
	
	virtual void Tick(const float DeltaSeconds) override;

	virtual void BeginPlay() override;

	AGarfield();
};
