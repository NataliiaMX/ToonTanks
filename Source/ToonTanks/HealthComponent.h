

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent //derived from UActorComponent
{
	GENERATED_BODY() //must remain on line 13

public:	
	UHealthComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;

	float CurrentHealth = 0.f;

	UFUNCTION()
	void HandleDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, 
						   class AController* Instigator, AActor* DamageCauser);

	class AToonTanksGameMode* GameMode;
};
