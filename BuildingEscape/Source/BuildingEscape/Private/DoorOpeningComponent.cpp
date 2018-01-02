// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "DoorOpeningComponent.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UDoorOpeningComponent::UDoorOpeningComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpeningComponent::BeginPlay()
{
	Super::BeginPlay();
	
	/// Initialization at runtime
    Door = GetOwner();

	///For Debugging purpose
	if (TriggerVolume == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trigger volume is missing from %s "), *Door->GetName());
	}
}


// Called every frame
void UDoorOpeningComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	HandleDoorEvent();
}

void UDoorOpeningComponent::HandleDoorEvent()
{
	if ((TriggerVolume != nullptr))
	{
		if (GetTotalMassOnTriggerVolume() > TriggerMass)
		{
			OnOpenRequest.Broadcast();
		}
		else 
		{
			OnCloseRequest.Broadcast();
		}
	}	
}

float UDoorOpeningComponent::GetTotalMassOnTriggerVolume()
{
	float TotalMass = .0f;
	TArray<AActor*> OverlappingActors;
	if (TriggerVolume == nullptr) {
		return  TotalMass;
	}
	TriggerVolume->GetOverlappingActors(OUT OverlappingActors);
	for (const AActor* actor : OverlappingActors) {
		TotalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT(" %s on trigger volume detected."), *(actor->GetName()));
	}
	return TotalMass;
}


