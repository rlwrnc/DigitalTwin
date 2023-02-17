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
	AGraphPoint* gp;
	// ...
	FActorSpawnParameters params;
	auto SpawnTransform = this->GetOwner()->GetTransform();
	gp = GetWorld()->SpawnActor<AGraphPoint>(AGraphPoint::StaticClass(), SpawnTransform);
}


// Called every frame
void UGraphController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

