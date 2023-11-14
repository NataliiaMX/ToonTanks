
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
 
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamageTaken);

	GameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}



void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::HandleDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, 
										AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	CurrentHealth-=Damage;

	if (CurrentHealth <= 0.f && GameMode)
	{
		GameMode->HanldeActorDeath(DamagedActor);
	}
}
