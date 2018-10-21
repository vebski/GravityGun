// Dawid Niemiec

#pragma once

#include "GravityGun.h"

#include "CoreMinimal.h"
#include "Game/Projectile/GGProjectileBase.h"
#include "GGProjectileTraced.generated.h"

/**
 *  Used for projectiles using physx traces for interaction with the world
 */
UCLASS()
class GRAVITYGUN_API AGGProjectileTraced : public AGGProjectileBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
		float TraceLength = 10000.0f;

	// Performs trace/overlaps against world, can be overriden to implement other types of tracing
	virtual void ProjectileTrace(TArray<FHitResult>& traceResults);

	virtual void ProcessHits(const TArray<FHitResult>& traceResults);

public:

	virtual void InitializeProjectile(AGGWeaponBase* owningWeapon) override;

	GG_FORCEINLINE float GetTraceLength() const
	{
		return TraceLength;
	}
};
