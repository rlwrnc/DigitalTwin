// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GraphController.generated.h"

#define MAX_POINTS 32

/*
	32 total x points spaced 15 units apart can be graphed.
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIGITALTWIN_API UGraphController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGraphController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	int plottedPoints[MAX_POINTS];		// will be an array of actors (the plotted points)
	int spawnLocation;					// will be a transform

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
