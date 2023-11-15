
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "EnemyTower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
    TargetTowers = GetTowerCount();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);
    }

    FTimerHandle PlayerEnableTimerHandle;
    FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, 
                                                   &AToonTanksPlayerController::SetPlayerEnabledState, true);

    GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
}

int32 AToonTanksGameMode::GetTowerCount()
{
    TArray<AActor*> Towers;
    UGameplayStatics::GetAllActorsOfClass(this, AEnemyTower::StaticClass(), Towers);
    return Towers.Num();
}

void AToonTanksGameMode::HanldeActorDeath(AActor* DeadActor)
{
    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if (ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
        HandleGameFinish(false);
    }
    else if(AEnemyTower* EnemyTower = Cast<AEnemyTower>(DeadActor))
    {
        EnemyTower->HandleDestruction();
        TargetTowers--;
        if(TargetTowers == 0)
        {
            HandleGameFinish(true);
            ToonTanksPlayerController->SetPlayerEnabledState(false);
        }
    }
}
