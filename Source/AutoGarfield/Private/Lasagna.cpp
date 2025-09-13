// Fill out your copyright notice in the Description page of Project Settings.


#include "Lasagna.h"

#include "Garfield.h"

// Sets default values
ALasagna::ALasagna()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComponent->SetupAttachment(BoxComponent);
}

void ALasagna::Tick(float DeltaSeconds)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(this->GetActorLocation().Z));
	if (this->GetActorLocation().Z < -10000)
	{
		this->Destroy();
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
		this->Destroy();
	}
}
