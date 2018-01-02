// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PickUpComponent.h"

#define OUT


// Sets default values for this component's properties
UPickUpComponent::UPickUpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPickUpComponent::BeginPlay()
{
	Super::BeginPlay();
	HandlePhysicHandleComponent();
	SetupInputComponent();
	
}

void UPickUpComponent::SetupInputComponent()
{
	FString OwnerName = GetOwner()->GetName();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("input component found on %s "), *OwnerName);
		InputComponent->BindAction("Pickup", IE_Pressed, this, &UPickUpComponent::Pickup);
		InputComponent->BindAction("Pickup", IE_Released, this, &UPickUpComponent::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("input component is missing from %s"), *OwnerName);
	}
}

void UPickUpComponent::HandlePhysicHandleComponent()
{
	FString OwnerName = GetOwner()->GetName();
	PhysicHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicHandleComponent) {
		UE_LOG(LogTemp, Warning, TEXT("physic handle component found on %s "), *OwnerName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("physic handle component is missing from %s"), *OwnerName);
	}
}

void UPickUpComponent::Pickup() {
	UE_LOG(LogTemp, Warning, TEXT("pickup is pressed"));
	if (IsRaycastHit(PlayerViewPointDirection,LineTraceEnd) == true) {
		UPrimitiveComponent* TargetComponent = HitResult.GetComponent();
		PhysicHandleComponent->GrabComponent(
			TargetComponent,
			NAME_None,
			TargetComponent->GetOwner()->GetActorLocation(),
			true
		);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Object on sight"));
	}
}

void UPickUpComponent::Release() {
	UE_LOG(LogTemp, Warning, TEXT("pickup is released"));
	PhysicHandleComponent->ReleaseComponent();
}


// Called every frame
void UPickUpComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdatePlayerViewPoint();

	if (PhysicHandleComponent->GrabbedComponent)
	{
		PhysicHandleComponent->SetTargetLocation(LineTraceEnd);
	}
}

void UPickUpComponent::UpdatePlayerViewPoint()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointDirection,
		OUT PlayerViewPointRotation
	);

	LineTraceDirection = PlayerViewPointRotation.Vector();
	LineTraceEnd = PlayerViewPointDirection + (LineTraceDirection*Reach);

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointDirection,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		2.f
	);
}

bool UPickUpComponent::IsRaycastHit(FVector &PlayerViewPointDirection,FVector &LineTraceEnd)
{
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	if (GetWorld()->LineTraceSingleByObjectType(OUT HitResult, PlayerViewPointDirection, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters)) {
		UE_LOG(LogTemp, Warning, TEXT("%s is hit"), *HitResult.GetActor()->GetName());
		return true;
	}
	else
	{
		return false;
	}
}

