

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"




UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY() //must remain on line 15
	
	public:
		void HanldeActorDeath(AActor* DeadActor);
	
	protected:
		virtual void BeginPlay() override;

	private:
		class ATank* Tank;

		class AToonTanksPlayerController* ToonTanksPlayerController;
};
