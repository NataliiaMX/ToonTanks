

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
		ATank();

		virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	protected:
		virtual void BeginPlay() override;

		UPROPERTY(EditAnywhere, Category = "Input")
		class UInputMappingContext* MainMappingContext;

		UPROPERTY(EditAnywhere, Category = "Input")
		class UInputAction* MoveAction;

		void Move(const FInputActionValue& Value);

	private:
		UPROPERTY(EditAnywhere, Category = "Components")
		class USpringArmComponent* SpringArm;
		
		UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCameraComponent* Camera;

		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float Speed = 200.f;
};
