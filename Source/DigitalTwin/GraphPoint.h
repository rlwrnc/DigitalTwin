// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GraphPoint.generated.h"

UCLASS()
class DIGITALTWIN_API AGraphPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGraphPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* Mesh;

public:	
	// Called every frame
	void SetMesh(const TCHAR* path);
};
