
#pragma once


#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"



UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY() //must remain on line 15

	public:
		virtual void Tick(float DeltaTime) override;
		ATank();

		virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	protected:
		virtual void BeginPlay() override;

		UPROPERTY(EditAnywhere, Category = "Input")
		class UInputMappingContext* MainMappingContext;

		UPROPERTY(EditAnywhere, Category = "Input")
		class UInputAction* MoveAction;

		UPROPERTY(EditAnywhere, Category = "Input")
		class UInputAction* FireAction;

		void Move(const FInputActionValue& Value);

		APlayerController* GetPlayerController();

		void SetupMappingContext();

	private:
		UPROPERTY(EditAnywhere, Category = "Components")
		class USpringArmComponent* SpringArm;
		
		UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCameraComponent* Camera;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float Speed = 200.f;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float TurnRate = 100.f;
};
