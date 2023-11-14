
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ToonTanksPlayerController.generated.h"





UCLASS()
class TOONTANKS_API AToonTanksPlayerController : public APlayerController
{
	GENERATED_BODY() //must remain on line 15

	public:
		void SetPlayerEnabledState(bool bPlayerEnabled); 
	
};
