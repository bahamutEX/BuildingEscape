// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DoorOpeningComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpeningComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpeningComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnCloseRequest;

	
private:

	///Exposed Properties

	//Initialize trigger volume
	UPROPERTY(EditAnywhere)
		ATriggerVolume* TriggerVolume = nullptr;

	UPROPERTY(EditAnywhere)
		float TriggerMass = 12.f;


	/// Functions Declaration

	void HandleDoorEvent();
	float GetTotalMassOnTriggerVolume();
	
	/// Hidden Properties
	AActor* Door;
};
