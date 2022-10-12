// Fill out your copyright notice in the Description page of Project Settings.


#include "Printer.h"

// Sets default values
APrinter::APrinter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APrinter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APrinter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

