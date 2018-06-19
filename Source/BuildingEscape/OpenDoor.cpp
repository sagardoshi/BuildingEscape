// Copyright Sagar Doshi 2018.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

#define OUT

/// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

/// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    
    if (!PressurePlate) UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
}

/// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If pressure sufficient, then open
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) OnOpen.Broadcast();
    else OnClose.Broadcast();
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
    float TotalMass = 0.f;
    
    // Find all overlapping actors
    TArray<AActor*> OverlappingActors;
    
    if (!PressurePlate) return TotalMass; // memory leak protection
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);
    
    // Iterate through and add actors
    for (const AActor* CurrentActor: OverlappingActors) {
        TotalMass += CurrentActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *CurrentActor->GetName())
    }
    
    return TotalMass;
}
