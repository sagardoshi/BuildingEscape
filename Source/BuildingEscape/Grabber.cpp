// Copyright Sagar Doshi 2018.

#include "Grabber.h"
#include "BuildingEscape.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "GameFramework/Character.h"
#include "Components/PrimitiveComponent.h"


#define OUT


/// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

/// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent() {
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (!PhysicsHandle) UE_LOG(LogTemp, Error, TEXT("%s is missing a PhysicsHandle."), *GetOwner()->GetName());
}

/// Look for attached Input Component
void UGrabber::SetInputComponent() {
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent) {
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabPress);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::GrabRelease);
    }
    else {UE_LOG(LogTemp, Warning, TEXT("Input component missing.")); }

}

/// Called when the game starts
void UGrabber::BeginPlay() {
	Super::BeginPlay();
    FindPhysicsHandleComponent();
    SetInputComponent();
}

/// Grabs object and attaches physics handle to it
void UGrabber::GrabPress() {
    
    // Line trace and see if we reach any actors with physics body collision channel set
    const FHitResult HitResult = GetFirstPhysicsBodyInReach();
    
    ComponentToGrab = HitResult.GetComponent(); // Gets mesh
    AActor* ActorHit = HitResult.GetActor();
    
    // If we hit something; attach a physics handle
    if (ActorHit) {
        PhysicsHandle->GrabComponentAtLocationWithRotation(
                                     ComponentToGrab,
                                     NAME_None, // No bones about it
                                     ComponentToGrab->GetOwner()->GetActorLocation(),
                                     ComponentToGrab->GetOwner()->GetActorRotation()
                                     );
    }
}

/// Drops held object
void UGrabber::GrabRelease() {
    PhysicsHandle->ReleaseComponent();
}
    
/// Fills location & rotation (called per tick)
void UGrabber::SetViewPoint() {
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation
                                                               );
}

/// Fills LineTraceEnd based on view point
void UGrabber::SetLineTrace() {
    LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}

/// Retrieves the first physics body the line trace hits
const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
    /// Get vector that reaches in direction of viewpoint
    SetViewPoint();
    SetLineTrace();
    
    /// Ray-cast to reach distance
    FHitResult HitResult;
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    bool hitFound = GetWorld()->LineTraceSingleByObjectType(
                                                            OUT HitResult,
                                                            PlayerViewPointLocation,
                                                            LineTraceEnd,
                                                            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
                                                            TraceParameters
                                                            );
    
    return HitResult;
}


/// Built-in function called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType,
							 FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    /// Get vector that reaches in direction of viewpoint
    SetViewPoint();
    SetLineTrace();
    
    // If physics handle attached, move object we are holding
    if (PhysicsHandle->GrabbedComponent) PhysicsHandle->SetTargetLocation(LineTraceEnd);
}


