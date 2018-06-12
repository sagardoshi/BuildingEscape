// Copyright Sagar Doshi 2018.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:
    // Applying macros to private attributes
    
    UPROPERTY(EditAnywhere)
    float AngleAjar = -90.0f;
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;
    
    UPROPERTY(EditAnywhere)
    float DoorCloseDelay = 0.125f;
    
//    UPROPERTY(EditAnywhere)
//    float TriggerMass = 50.0f;
    
    // Non-macro attributes
    float OpenAngle;
    float CloseAngle;
    float LastDoorOpenTime;
    
    AActor* Owner; // Owning door
    
    // Key for puzzle - table + chair needed
    float GetTotalMassOfActorsOnPlate();
    
public:
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor();
	void CloseDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


};
