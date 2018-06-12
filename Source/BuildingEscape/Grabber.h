// Copyright Sagar Doshi 2018.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

private:
	float Reach = 100.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
    UInputComponent* InputComponent = nullptr;
    UPrimitiveComponent* ComponentToGrab = nullptr;
    
    // Ray-cast and grab what's in reach
    void GrabPress();
    void GrabRelease();
    
    // Set up physics and inputs;
    void FindPhysicsHandleComponent();
    void SetUpInputComponent();
    
    // Return hit for first physics body in reach
    const FHitResult GetFirstPhysicsBodyInReach();
    

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



};
