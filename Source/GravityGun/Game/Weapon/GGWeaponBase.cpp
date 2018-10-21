// Dawid Niemiec

#include "GGWeaponBase.h"

#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "../Character/GGCharacter.h"
#include "../Projectile/GGProjectileBase.h"

AGGWeaponBase::AGGWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	WeaponRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponRootComponent"));
	SetRootComponent(WeaponRootComponent);

	MuzzleComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("MuzzleComponent"));
	MuzzleComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMeshComponent"));
	WeaponMeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform); // #TODO_Dawid weapon socket ??
	WeaponMeshComponent->SetCastShadow(false);

}

void AGGWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGGWeaponBase::UpdateWeapon(float deltaTime)
{
	CurrentEquipCooldown = FMath::Max(0.0f, CurrentEquipCooldown - deltaTime);
	CurrentPrimaryFirerateCooldown = FMath::Max(0.0f, CurrentPrimaryFirerateCooldown - deltaTime);
	CurrentSecondaryFirerateCooldown = FMath::Max(0.0f, CurrentSecondaryFirerateCooldown - deltaTime);

	if (bIsEquipped == true && CurrentEquipCooldown <= 0.0f)
	{
		bIsReady = true;
	}

	if (CanFire() == true)
	{
		if (CanFirePrimary() == true)
		{
			PrimaryFire();

			if (bIsPrimarySingleFire == true)
			{
				bIsPrimaryFireActive = false;
			}
		}
		else if (CanFireSecondary() == true)
		{
			SecondaryFire();

			if (bIsSecondarySingleFire == true)
			{
				bIsSecondaryFireActive = false;
			}
		}
	}	
}

void AGGWeaponBase::PrimaryFire()
{
	CurrentPrimaryFirerateCooldown = PrimaryFirerateCooldown;

	SpawnProjectile(PrimaryProjectileTemplate);
}

void AGGWeaponBase::SecondaryFire()
{
	CurrentSecondaryFirerateCooldown = SecondaryFirerateCooldown;

	SpawnProjectile(SecondaryProjectileTemplate);
}

void AGGWeaponBase::ShowWeaponVisuals()
{
	WeaponMeshComponent->SetVisibility(true, true);
}

void AGGWeaponBase::HideWeaponVisuals()
{
	WeaponMeshComponent->SetVisibility(false, true);
}

void AGGWeaponBase::CompleteEquip()
{
	// #TODO_Dawid this can be used in future to expand functionality (when inventory and picking up weapons works)
}

void AGGWeaponBase::CompleteUnequip()
{
	// #TODO_Dawid this can be used in future to expand functionality (when inventory and picking up weapons works)
}

AGGProjectileBase* AGGWeaponBase::SpawnProjectile(TSubclassOf<AGGProjectileBase> projectileTemplate)
{
	FTransform spawnTransform = CalculateProjectileSpawnTransform(projectileTemplate);

	AGGProjectileBase* newProjectile = GetWorld()->SpawnActor<AGGProjectileBase>(projectileTemplate, spawnTransform);
	newProjectile->InitializeProjectile(this);


	return newProjectile;
}

bool AGGWeaponBase::CanFirePrimary() const
{
	return bIsPrimaryFireActive == true && CurrentPrimaryFirerateCooldown <= 0.0f;
}

bool AGGWeaponBase::CanFireSecondary() const
{
	return bIsSecondaryFireActive == true && CurrentSecondaryFirerateCooldown <= 0.0f;
}

FTransform AGGWeaponBase::CalculateProjectileSpawnTransform(TSubclassOf<AGGProjectileBase> projectileTemplate) const
{
	FTransform spawnTransform = MuzzleComponent->GetComponentTransform();
	// check if projectile wants to spawn at center view and weapon is used by character with camera
	if (projectileTemplate.GetDefaultObject() != nullptr && projectileTemplate.GetDefaultObject()->ShouldSpawnAtViewCenter())
	{
		if (GetOwningCharacter() != nullptr && GetOwningCharacter()->GetCameraComponent() != nullptr)
		{
			spawnTransform = GetOwningCharacter()->GetCameraComponent()->GetComponentTransform();
		}
	}

	return spawnTransform;
}

// Called every frame
void AGGWeaponBase::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	UpdateWeapon(deltaTime);
}

void AGGWeaponBase::Equip()
{
	if (OwningCharacter != nullptr)
	{
		AttachToComponent(OwningCharacter->GetWeaponAttachmentComponent(), FAttachmentTransformRules::KeepRelativeTransform, OwningCharacter->GetWeaponSocketName());
	}

	
	bIsReady = true; // #TODO_Dawid move to CompleteEquip when Equip/Unequip system is working
	bIsEquipped = true;
}

void AGGWeaponBase::Unequip()
{
	bIsPrimaryFireActive = false;
	bIsSecondaryFireActive = false;
}

void AGGWeaponBase::StartPrimaryFire()
{
	bIsPrimaryFireActive = true;
}

void AGGWeaponBase::StopPrimaryFire()
{
	bIsPrimaryFireActive = false;
}

void AGGWeaponBase::StartSecondaryFire()
{
	bIsSecondaryFireActive = true;
}

void AGGWeaponBase::StopSecondaryFire()
{
	bIsSecondaryFireActive = false;
}

bool AGGWeaponBase::CanFire() const
{
	return bIsEquipped == true && bIsReady == true && OwningCharacter != nullptr;
}

void AGGWeaponBase::SetOwningCharacter(AGGCharacter* owningCharacter)
{
	OwningCharacter = owningCharacter;
}

AGGCharacter* AGGWeaponBase::GetOwningCharacter() const
{
	return OwningCharacter;
}

UArrowComponent* AGGWeaponBase::GetMuzzleComponent() const
{
	return MuzzleComponent;
}

