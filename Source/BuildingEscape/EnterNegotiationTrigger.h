// Copyright Sagar Doshi 2018.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "EnterNegotiationTrigger.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UEnterNegotiationTrigger : public UActorComponent
{
	GENERATED_BODY()

//private:
    
    
public:	
	// Sets default values for this component's properties
	UEnterNegotiationTrigger();
    
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LevelToLoad;
    
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	
};
