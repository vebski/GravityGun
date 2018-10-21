// Dawid Niemiec

#include "GGWeaponGravityGun.h"

#include "Components/SkeletalMeshComponent.h"
#include "../GGPhysicsItem.h"
#include "Components/ArrowComponent.h"
#include "GGGravityPullComponent.h"
#include "../Character/GGCharacter.h"
#include "../Projectile/Traced/GGProjectileTraced.h"

AGGWeaponGravityGun::AGGWeaponGravityGun()
{
	PullTargetComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PullTargetComponent"));
	PullTargetComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	GravityPullComponent = CreateDefaultSubobject<UGGGravityPullComponent>(TEXT("GravityPullComponent"));
	GravityPullComponent->SetPullTargetComponent(PullTargetComponent);
}

void AGGWeaponGravityGun::BeginPlay()
{
	Super::BeginPlay();

	GravityPullComponent->SetOwningWeapon(this);
}

void AGGWeaponGravityGun::PrimaryFire()
{
	// If we are pulling and object stop, and shoot (if there is any object fully pulled we will shoot it instead sending it forwards)
	if (GravityPullComponent->IsPullingItem())
	{
		GravityPullComponent->StopPullingItem();
	}

	Super::PrimaryFire();
}

void AGGWeaponGravityGun::SecondaryFire()
{
	if (GravityPullComponent->IsPullingItem())
	{
		// stop pulling the object instead of firing projectile
		GravityPullComponent->StopPullingItem();
		CurrentSecondaryFirerateCooldown = SecondaryFirerateCooldown;
	}
	else
	{
		Super::SecondaryFire();
		// Rest cooldown to allow players to cancel immediately 
		CurrentSecondaryFirerateCooldown = 0.0f;
	}
}

bool AGGWeaponGravityGun::CheckTraceForProjectile(TSubclassOf<AGGProjectileBase> projectileTemplate) const
{
	FTransform spawnTransform = CalculateProjectileSpawnTransform(projectileTemplate);

	// #TODO_Dawid this could be probably better if projectiles had function that could provide uniform behavior instead of rewriting it
	AGGProjectileTraced* projectileTrace = projectileTemplate->GetDefaultObject<AGGProjectileTraced>();
	check(projectileTrace != nullptr);

	const FVector traceStart = spawnTransform.GetLocation();
	const FVector traceEnd = traceStart + (spawnTransform.GetRotation().GetForwardVector() * projectileTrace->GetTraceLength());

	FCollisionQueryParams queryParams;
	queryParams.bTraceComplex = true;

	// Add weapon and its owner to ignore list so we avoid their collision
	queryParams.AddIgnoredActor(this);
	queryParams.AddIgnoredActor(GetOwningCharacter());

	FHitResult hit;
	GetWorld()->LineTraceSingleByChannel(hit, traceStart, traceEnd, ECC_TRACE_PROJECTILE, queryParams);

	if (hit.bBlockingHit == true && hit.GetActor() != nullptr)
	{
		return Cast<AGGPhysicsItem>(hit.GetActor()) != nullptr;
	}

	return false;
}

void AGGWeaponGravityGun::PullPhysicsItem(AGGPhysicsItem* physicsItem)
{
	GravityPullComponent->StartPullingItem(physicsItem);
}

bool AGGWeaponGravityGun::CanPushItem() const
{
	return CheckTraceForProjectile(PrimaryProjectileTemplate);
}

bool AGGWeaponGravityGun::CanPullItem() const
{
	return CheckTraceForProjectile(SecondaryProjectileTemplate);
}
