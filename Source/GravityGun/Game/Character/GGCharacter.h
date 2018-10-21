// Dawid Niemiec

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GGCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class GRAVITYGUN_API AGGCharacter : public ACharacter
{
	GENERATED_BODY()


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visuals")
	FName WeaponSocketName = FName(TEXT("GripPoint"));

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals")
	USkeletalMeshComponent* FPArmsMeshComponent = nullptr;

	AGGCharacter();
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FName GetWeaponSocketName() const;

	virtual USkeletalMeshComponent* GetWeaponAttachmentComponent() const;

	UCameraComponent* GetCameraComponent() const;
};
