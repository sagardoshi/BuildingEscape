// Copyright Sagar Doshi 2018.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:
    // Applying macros to private attributes
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;
   
    UPROPERTY(EditAnywhere)
    float TriggerMass = 30.f;
    
    // Key for puzzle - table + chair needed
    float GetTotalMassOfActorsOnPlate();
    
public:
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(BlueprintAssignable)
    FDoorEvent OnOpen;
    
    UPROPERTY(BlueprintAssignable)
    FDoorEvent OnClose;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
