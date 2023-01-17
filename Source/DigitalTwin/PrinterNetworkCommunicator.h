// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include "TimerManager.h"
#include "Components/ActorComponent.h"
#include "HTTP.h"
#include "Json.h"
#include "Components/TextRenderComponent.h"
#include "PrinterNetworkCommunicator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIGITALTWIN_API UPrinterNetworkCommunicator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPrinterNetworkCommunicator();

protected:
	UTextRenderComponent* TemperatureText;
	AActor xAxis, yAxis, zAxis;
	bool isRunningJob;
	double toolTemp, bedTemp;
	FTimerHandle TemperatureHandle;

	// Called when the game starts
	virtual void BeginPlay() override;
	void PollTemperature();
	void UpdateTemperatureText();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool success);
};
