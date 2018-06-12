// Copyright Sagar Doshi 2018.

#include "Grabber.h"
#include "BuildingEscape.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "GameFramework/Character.h"
#include "Components/PrimitiveComponent.h"


#define OUT


// Sets default values for this component's properties
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
void UGrabber::SetUpInputComponent() {
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent) {
        UE_LOG(LogTemp, Warning, TEXT("Correctly detected the input component."));
        
        // Bind the input axis
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabPress);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::GrabRelease);
    }
    else {UE_LOG(LogTemp, Warning, TEXT("Input component missing.")); }

}

// Called when the game starts
void UGrabber::BeginPlay() {
	Super::BeginPlay();
    FindPhysicsHandleComponent();
    SetUpInputComponent();
}

/// Grabbing Logs
void UGrabber::GrabPress() {
    UE_LOG(LogTemp, Warning, TEXT("Grab pressed."));
    
    // Line trace and see if we reach any actors with physics body collision channel set
    const FHitResult HitResult = GetFirstPhysicsBodyInReach();
    
    ComponentToGrab = HitResult.GetComponent();
    AActor* ActorHit = HitResult.GetActor();
    
    // If we hit something; attach a physics handle
    if (ActorHit) {
        // attach physics handle
        PhysicsHandle->GrabComponentAtLocationWithRotation(
                                     ComponentToGrab,
                                     NAME_None, // No bones about it
                                     ComponentToGrab->GetOwner()->GetActorLocation(),
                                     ComponentToGrab->GetOwner()->GetActorRotation()
                                     );
    }
}
void UGrabber::GrabRelease() {
    UE_LOG(LogTemp, Warning, TEXT("Grab released."));
    // Release physics handle
}

/// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType,
							 FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    ////////////////////////////////////////////////////////////
    /// Get player viewpoint this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
        );
    
    /// Draw a red trace in the world to visualise
    FVector LineTraceDirection = PlayerViewPointRotation.Vector();
    FVector LineTraceEnd = PlayerViewPointLocation + (LineTraceDirection * Reach);
    
    ////////////////////////////////////////////////////////////
    
    // If physics handle attached, move object we are holding
    if (PhysicsHandle->GrabbedComponent) {
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
        
    }
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
    /// Get player viewpoint this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
        );
    
    /// Draw a red trace in the world to visualise
    FVector LineTraceDirection = PlayerViewPointRotation.Vector();
    FVector LineTraceEnd = PlayerViewPointLocation + (LineTraceDirection * Reach);
    
    /// Setup query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    /// Ray-cast to reach distance
    FHitResult Hit;
    bool hitFound = GetWorld()->LineTraceSingleByObjectType(
        OUT Hit,
        PlayerViewPointLocation,
        LineTraceEnd,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParameters
        );
    
    /// Log name of any object that was hit
//    FString hitName;
//    if (hitFound) {
//        hitName = Hit.GetActor()->GetName();
        //        UE_LOG(LogTemp, Warning, TEXT("Currently hitting: %s"), *hitName);
//    }
    return Hit;
}
