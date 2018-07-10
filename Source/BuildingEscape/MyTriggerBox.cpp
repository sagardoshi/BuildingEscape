// Copyright Sagar Doshi 2018.

#define print(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, FString::Printf(TEXT(text), fstring))


#include "MyTriggerBox.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"


AMyTriggerBox::AMyTriggerBox()
{
    OnActorBeginOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapEnd);
}

void AMyTriggerBox::BeginPlay()
{
    Super::BeginPlay();
    
    DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
    
    
}

void AMyTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
    if(OtherActor && (OtherActor != this))
    {
        print("Overlap Begin");
        printFString("Overlapped Actor = %s", *OverlappedActor->GetName());

    }
}

void AMyTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
    if(OtherActor && (OtherActor != this))
    {
        print("Overlap Ended");
        printFString("Overlapped Actor = %s", *OtherActor->GetName());
    }
}


