// Copyright Sagar Doshi 2018.

#pragma once

#include "Engine.h"
#include "Engine/TriggerBox.h"
#include "MyTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGESCAPE_API AMyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

private:
    const FName EncounterLevelName = FName(TEXT("2DEncounter"));
    
protected:
    virtual void BeginPlay() override;
    
public:
    AMyTriggerBox();
    
    UFUNCTION()
    void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
    
    UFUNCTION()
    void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);
    
	
};
