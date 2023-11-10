


#include "HealthComponent.h"

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

	UE_LOG(LogTemp, Display, TEXT("Health: %f"), CurrentHealth);
	UE_LOG(LogTemp, Display, TEXT("Damaged actor: %s"), *DamagedActor->GetActorNameOrLabel());
}
