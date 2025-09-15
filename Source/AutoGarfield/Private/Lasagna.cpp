// Fill out your copyright notice in the Description page of Project Settings.


#include "Lasagna.h"

#include "Garfield.h"

int ALasagna::TotalNumberSpawned;
int ALasagna::NumberEaten;

// Sets default values
ALasagna::ALasagna()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComponent->SetupAttachment(BoxComponent);

	TotalNumberSpawned += 1;

}

void ALasagna::Tick(float DeltaSeconds)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(this->GetActorLocation().Z));
	if (this->GetActorLocation().Z < -10000)
	{
		this->Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Format(TEXT("Number eaten = {0}; Total number = {1}; Percentage = {2}%"), { NumberEaten, TotalNumberSpawned, double(NumberEaten) / double(TotalNumberSpawned) * 100 }));

	}
}


// Called when the game starts or when spawned
void ALasagna::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ALasagna::OnOverlapBegin);
}

void ALasagna::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Lasagna Begin Overlap");
	if (Cast<AGarfield>(OtherActor))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Lasagna Destroy");
		NumberEaten += 1;
		this->Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Format(TEXT("Number eaten = {0}; Total number = {1}; Percentage = {2}%"), { NumberEaten, TotalNumberSpawned, double(NumberEaten) / double(TotalNumberSpawned) * 100 }));


	}
}
