// Copyright Sagar Doshi 2018.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// From scene, saves pointer to player's current body into ActorThatOpens
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Establishes owner and default door angles at start
	Owner = GetOwner();
	CloseAngle = Owner->GetActorRotation().Yaw;
	OpenAngle = CloseAngle + AngleAjar;
}

void UOpenDoor::OpenDoor() {
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor() {
	Owner->SetActorRotation(FRotator(0.f, CloseAngle, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float Now = GetWorld()->GetTimeSeconds();


	// If PressurePlate pressed, then open
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
		LastDoorOpenTime = Now;
	}

	// If PressurePlate left, then close
	if (Now > (LastDoorOpenTime + DoorCloseDelay)) {
		CloseDoor();
	}
}
