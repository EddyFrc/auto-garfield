// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Lasagna.generated.h"

UCLASS()
class AUTOGARFIELD_API ALasagna : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;

	static int NumberEaten;
	static int TotalNumberSpawned;
	
	// Sets default values for this actor's properties
	ALasagna();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable)
	static FString GetDisplayCatchPercentage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
