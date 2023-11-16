
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ParticleTrailComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle"));
	ParticleTrailComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 1300.f;
	ProjectileMovementComponent->MaxSpeed = 2000.f;
}


void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}



void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* HitedActor, 
                        UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult &Hit)
{
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	AActor* MyOwner = GetOwner();
	if(MyOwner == nullptr)
	{
		Destroy();
		return;
	}
	
	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

	UClass* DamageTypeClass = UDamageType::StaticClass();

	if(HitedActor && HitedActor != this && HitedActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(HitedActor, Damage, MyOwnerInstigator, this, DamageTypeClass);

		if(HitEffectParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitEffectParticle, GetActorLocation(), GetActorRotation());
		}
		if(HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
	Destroy();
}
