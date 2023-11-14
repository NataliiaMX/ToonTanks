
#include "EnemyTower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AEnemyTower::AEnemyTower()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEnemyTower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();

}

void AEnemyTower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTower::CheckFireDistance, FireRate, true);
}

void AEnemyTower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (IsPawnInRange())
    {
        FVector TankLocation = Tank->GetActorLocation();
        RotateTurret(TankLocation);
    }  
}

void AEnemyTower::CheckFireDistance()
{
    if (IsPawnInRange())
    {
        Fire();
    }
}

bool AEnemyTower::IsPawnInRange()
{
    if (Tank != nullptr)
    {
        FVector TankLocation = Tank->GetActorLocation();
        float Distance = FVector::Dist(GetActorLocation(), TankLocation);
        return Distance <= FireRange;
    }
    return false;
}
