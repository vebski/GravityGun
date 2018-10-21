// Dawid Niemiec

#include "GGCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"


AGGCharacter::AGGCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
	CameraComponent->bUsePawnControlRotation = true;

	FPArmsMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPArmsMeshComponent"));
	FPArmsMeshComponent->AttachToComponent(CameraComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FPArmsMeshComponent->SetCastShadow(false);
}

void AGGCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AGGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

FName AGGCharacter::GetWeaponSocketName() const
{
	return WeaponSocketName;
}

USkeletalMeshComponent* AGGCharacter::GetWeaponAttachmentComponent() const
{
	return FPArmsMeshComponent;
}

UCameraComponent* AGGCharacter::GetCameraComponent() const
{
	return CameraComponent;
}

