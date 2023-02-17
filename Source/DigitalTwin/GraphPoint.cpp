// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphPoint.h"

// Sets default values
AGraphPoint::AGraphPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	Mesh->SetStaticMesh(LoadObject<UStaticMesh>(NULL, TEXT("/Engine/EngineMeshes/Sphere.Sphere")));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AGraphPoint::BeginPlay()
{
	Super::BeginPlay();
}

void AGraphPoint::SetMesh(const TCHAR* path)
{
	auto material = LoadObject<UMaterialInterface>(NULL, path);
	Mesh->SetMaterial(0, material);
}
