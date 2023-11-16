
#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
    Super::BeginPlay();

}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(GetPlayerController())
    {
        FHitResult HitResult;
        GetPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
        RotateTurret(HitResult.ImpactPoint);
    }
}

//movement
void ATank::Move(const FInputActionValue &Value)
{
    FVector2D CurrentValue = Value.Get<FVector2D>();
    FVector Offset3D(CurrentValue.X, 0.0f, 0.0f);
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    FVector DeltaLocation = Offset3D * Speed * DeltaTime;
    bool DoesSweep = true;
    AddActorLocalOffset(DeltaLocation, DoesSweep);
    
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = CurrentValue.Y * TurnRate * DeltaTime;  
    AddActorLocalRotation(DeltaRotation, DoesSweep);
}


//controller and input setup
APlayerController* ATank::GetPlayerController()
{
    APlayerController* PlayerController = Cast<APlayerController>(Controller);
    return PlayerController;
}

void ATank::SetupMappingContext()
{
    if(GetPlayerController())
    {
        UEnhancedInputLocalPlayerSubsystem* Subsystem = 
                    ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetPlayerController()->GetLocalPlayer());
        if(Subsystem)
        {
            Subsystem->AddMappingContext(MainMappingContext, 0);
        }
    }
}

void ATank::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    SetupMappingContext();
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATank::Fire);
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}
