// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphController.h"

// Sets default values for this component's properties
UGraphController::UGraphController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

// Called when the game starts
void UGraphController::BeginPlay()
{
	Super::BeginPlay();
	// ...
	startLocation = this->GetOwner()->GetTransform();
	// y=485 to allow for 32 plotted points at current size
	// we can probably do better, but this is a bit of a hack job anyhows
	startLocation.AddToTranslation(FVector(0.0f, 485.0f, 0.0f));

	auto aClass = AGraphPoint::StaticClass();
	auto gp = GetWorld()->SpawnActorDeferred<AGraphPoint>(AGraphPoint::StaticClass(), startLocation);
	gp->SetMesh(TEXT("/Game/Materials/Floor.Floor"));
	gp->FinishSpawning(startLocation);
}


// Called every frame
void UGraphController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

