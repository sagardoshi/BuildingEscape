// Copyright Sagar Doshi 2018.

#pragma once


#include <vector>
#include <iostream>
#include <string>
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NegotiationsUI.generated.h"


UCLASS()
class BUILDINGESCAPE_API ANegotiationsUI : public AHUD
{
	GENERATED_BODY()
    
private:
    std::vector<std::string> dialogue;
    
public:
    ANegotiationsUI(); // Constructor
    
    void AdvanceDialogue();
	
	
	
};
