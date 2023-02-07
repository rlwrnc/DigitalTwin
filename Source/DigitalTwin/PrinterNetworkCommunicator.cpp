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

UPrinterNetworkCommunicator::~UPrinterNetworkCommunicator()
{
}

// Called when the game starts
void UPrinterNetworkCommunicator::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// initialize temperature text
	TemperatureText = this->GetOwner()->FindComponentByClass<UTextRenderComponent>();
	toolTemp = 0.0f, bedTemp = 0.0f;
	TemperatureText->SetText(FText::FromString(FString::Printf(TEXT("Tool: %2.2f°\nBed: %2.2f°"), toolTemp, bedTemp)));

	// timer setup
	GetWorld()->GetTimerManager().SetTimer(TemperatureHandle, this, &UPrinterNetworkCommunicator::PollTemperature, 1.0f, true, 0.0f);
}

/*
 * TODO:
 * - variadic function for response body (needs to be variadic because we will have more than one printer?
*/

// Called every frame
void UPrinterNetworkCommunicator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	
}

/**
* @brief creates and sends http get request for temperature, updates printer text
*/
void UPrinterNetworkCommunicator::PollTemperature()
{
	// create/send http get request
	FHttpRequestPtr request = FHttpModule::Get().CreateRequest();
	request->OnProcessRequestComplete().BindUObject(this, &UPrinterNetworkCommunicator::OnResponseReceived);
	//request->SetURL("http://192.168.1.101/api/printer");
	request->SetURL(BaseURL + FString("api/printer"));
	request->SetVerb("GET");
	request->SetHeader(FString("X-Api-Key"), APIKey);
	request->ProcessRequest();

	//update temperature text
	TemperatureText->SetText(FText::FromString(FString::Printf(TEXT("Head: %2.2f°\nBed: %2.2f°"), toolTemp, bedTemp)));
	WriteTemperature();
}

void UPrinterNetworkCommunicator::OnResponseReceived(FHttpRequestPtr request, FHttpResponsePtr response, bool success)
{
	FString requestVerb = *request->GetVerb();
	if (requestVerb.Equals("GET")) {
		//UE_LOG(LogTemp, Display, TEXT("HTTP Response: %s"), *response->GetContentAsString());
		// parse temperature
		TSharedPtr<FJsonObject> responseObj;

		TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(response->GetContentAsString());
		FJsonSerializer::Deserialize(reader, responseObj);
		TSharedPtr<FJsonObject> tempObj = responseObj->GetObjectField("temperature");
		
		toolTemp = tempObj->GetObjectField("tool0")->GetNumberField("actual");
		bedTemp = tempObj->GetObjectField("bed")->GetNumberField("actual");
		WriteTemperature();
	}
}

void UPrinterNetworkCommunicator::UpdateTemperatureText()
{

}

void UPrinterNetworkCommunicator::WriteTemperature()
{
	FString file = FPaths::ProjectDir().Append("data.csv");
	FDateTime timestamp = FDateTime::Now();
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	FString writeString = FString::Printf(
		TEXT("%d-%d-%d %d:%d:%d,%lf,%lf\n"),
		timestamp.GetMonth(), timestamp.GetDay(), timestamp.GetYear(),
		timestamp.GetHour(), timestamp.GetMinute(), timestamp.GetSecond(),
		toolTemp, bedTemp);
	if (FileManager.FileExists(*file))
		FFileHelper::SaveStringToFile(
			writeString,
			*file, 
			FFileHelper::EEncodingOptions::AutoDetect,	// default value
			&IFileManager::Get(),						// default value
			EFileWrite::FILEWRITE_Append
		);
}