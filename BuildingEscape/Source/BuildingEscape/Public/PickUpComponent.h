// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PickUpComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UPickUpComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPickUpComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	


private:

	///Hidden Properties

	//Define player's reach (range) constant
	float const Reach = 100.f;

	//Define physics handle component for checking and usage
	UPhysicsHandleComponent* PhysicHandleComponent = nullptr;

	//Define input component for checking and usage
	UInputComponent* InputComponent = nullptr;

	FHitResult HitResult;

	FVector PlayerViewPointDirection;

	FRotator PlayerViewPointRotation;

	FVector LineTraceDirection;

	FVector LineTraceEnd;

	///Functions Declaration

	// Handles picking up object
	void Pickup();

	// Handles releasing object
	void Release();

	// Handles physic handle component
	void HandlePhysicHandleComponent();

	// Setting up input component
	void SetupInputComponent();

	void UpdatePlayerViewPoint();

	// Handles raycasting 
	// @ Output : Hit result
	bool IsRaycastHit(FVector &PlayerViewPointDirection, FVector &LineTraceEnd);
};
