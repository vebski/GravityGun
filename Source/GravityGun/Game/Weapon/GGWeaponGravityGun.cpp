// Dawid Niemiec

#include "GGWeaponGravityGun.h"

#include "Components/SkeletalMeshComponent.h"
#include "../GGPhysicsItem.h"
#include "Components/ArrowComponent.h"
#include "GGGravityPullComponent.h"


AGGWeaponGravityGun::AGGWeaponGravityGun()
{
	PullTargetComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PullTargetComponent"));
	PullTargetComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	GravityPullComponent = CreateDefaultSubobject<UGGGravityPullComponent>(TEXT("GravityPullComponent"));
	GravityPullComponent->SetPullTargetComponent(PullTargetComponent);
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

void AGGWeaponGravityGun::PullPhysicsItem(AGGPhysicsItem* physicsItem)
{
	GravityPullComponent->StartPullingItem(physicsItem);
	//if (physicsItem != nullptr)
	//{
	//	AttachedItem = physicsItem;
	//	AttachedItem->GetMainComponent()->BodyInstance.SetInstanceSimulatePhysics(false);
	//	AttachedItem->SetActorEnableCollision(false);
	//	AttachedItem->AttachToComponent(GetMuzzleComponent(), FAttachmentTransformRules::KeepWorldTransform);
	//	//AttachedItem->Attach
	//}
}