// Dawid Niemiec

#include "GGProjectileGravityPull.h"
#include "DrawDebugHelpers.h"
#include "Game/GGPhysicsItem.h"
#include "Game/Weapon/GGWeaponGravityGun.h"
#include "Components/ArrowComponent.h"


void AGGProjectileGravityPull::ProcessHits(const TArray<FHitResult>& traceResults)
{
	if (traceResults.Num() > 0)
	{
		for (int32 tr = 0; tr < traceResults.Num(); ++tr)
		{
			DrawDebugSphere(GetWorld(), traceResults[tr].ImpactPoint, 10.0f, 6, FColor::Green, false, 3.0f, 0, 5.0f);
		}

		// check if we traced any objects we can pull
		const FHitResult& blockingHit = traceResults.Last();
		if (traceResults.Last().bBlockingHit && blockingHit.Actor.Get() != nullptr)
		{
			AGGPhysicsItem* blockingActor = Cast<AGGPhysicsItem>(blockingHit.Actor.Get());
			if (blockingActor != nullptr)
			{
				if (blockingActor->IsBigItem(MaxItemExtent) == true)
				{
					Super::ProcessHits(traceResults);
				}
				else
				{
					StartPulling(blockingActor);
				}
			}
		}

	}

	DestroyProjectile();
}

void AGGProjectileGravityPull::StartPulling(AGGPhysicsItem* physicsItem)
{
	AGGWeaponGravityGun* gravityGun = Cast<AGGWeaponGravityGun>(OwningWeapon);
	check(gravityGun != nullptr); // this projectile has to be used in gravity gun!

	gravityGun->PullPhysicsItem(physicsItem);
}

FVector AGGProjectileGravityPull::CalculateImpulseDir(const FHitResult& traceResult) const
{
	return Super::CalculateImpulseDir(traceResult) * -1.0f;
}
