
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

 
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 1300.f;
	ProjectileMovementComponent->MaxSpeed = 2000.f;
}


void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}



void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* HitedActor, 
                        UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult &Hit)
{
	if(HitedActor->GetName() == TEXT("Floor_0"))
	{
		return;
	}
	UE_LOG(LogTemp, Display, TEXT("Hit Component: %s"), *HitComponent->GetName());
	UE_LOG(LogTemp, Display, TEXT("Hited Actor: %s"), *HitedActor->GetName());
	UE_LOG(LogTemp, Display, TEXT("Other Component: %s"), *OtherComponent->GetName());
}
