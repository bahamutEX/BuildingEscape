// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PositionReporting.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReporting::UPositionReporting()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//TestLogging
	UE_LOG(LogTemp,Warning,TEXT("Position Reporting on duty"));
	// ...
}


// Called when the game starts
void UPositionReporting::BeginPlay()
{
	Super::BeginPlay();

	FString objectName = GetOwner()->GetName();
	FString objectPosition = GetOwner()->GetTransform().GetLocation().ToString();
	
	UE_LOG(LogTemp,Warning,TEXT("Current position of %s = %s"),*objectName,*objectPosition);
	// ...
	
}


// Called every frame
void UPositionReporting::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

