// Fill out your copyright notice in the Description page of Project Settings.


#include "PrinterNetworkCommunicator.h"

// Sets default values for this component's properties
UPrinterNetworkCommunicator::UPrinterNetworkCommunicator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPrinterNetworkCommunicator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FHttpRequestPtr request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> requestObj = MakeShared<FJsonObject>();
	requestObj->SetStringField(FString("command"), FString("jog"));
	requestObj->SetNumberField(FString("x"), 10);
	requestObj->SetNumberField(FString("y"), -5);
	requestObj->SetNumberField(FString("z"), 0.02);

	FString requestBody;
	TSharedRef<TJsonWriter<>> writer = TJsonWriterFactory<>::Create(&requestBody);
	FJsonSerializer::Serialize(requestObj, writer);

	request->OnProcessRequestComplete().BindUObject(this, &UPrinterNetworkCommunicator::OnResponseReceived);
	request->SetURL(FString("http://192.168.1.101/api/printer/printhead"));
	request->SetVerb(FString("POST"));
	request->SetHeader(FString("X-Api-Key"), FString("CA29191915284A00A0207FB0213F0275"));
	request->AppendToHeader(FString("Content-Type"), FString("application/json"));
	request->SetContentAsString(requestBody);
	request->ProcessRequest();
}


// Called every frame
void UPrinterNetworkCommunicator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPrinterNetworkCommunicator::OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool success)
{
	UE_LOG(LogTemp, Display, TEXT("HTTP Response: %s"), *response->GetContentAsString());
}