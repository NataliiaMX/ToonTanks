
#include "EnemyTower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

AEnemyTower::AEnemyTower()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEnemyTower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AEnemyTower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Tank != nullptr)
    {
        FVector TankLocation = Tank->GetActorLocation();

        float Distance = FVector::Dist(GetActorLocation(), TankLocation);
        if (Distance <= FireRange)
        {
            RotateTurret(TankLocation);
        }
    }
}