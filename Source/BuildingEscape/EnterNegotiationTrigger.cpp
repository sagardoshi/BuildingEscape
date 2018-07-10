// Copyright Sagar Doshi 2018.

#include "EnterNegotiationTrigger.h"


// Sets default values for this component's properties
UEnterNegotiationTrigger::UEnterNegotiationTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnterNegotiationTrigger::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnterNegotiationTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

