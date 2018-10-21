// Dawid Niemiec

#pragma once

#include "GravityGun.h"

#include "CoreMinimal.h"
#include "GGProjectileGravityBeam.h"
#include "GGProjectileGravityPull.generated.h"

class USceneComponent;

class AGGPhysicsItem;

/**
 * 
 */
UCLASS()
class GRAVITYGUN_API AGGProjectileGravityPull : public AGGProjectileGravityBeam
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	float MaxItemExtent = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	float PullForce = 30000.0f;

	virtual void ProcessHits(const TArray<FHitResult>& traceResults) override;

	virtual void StartPulling(AGGPhysicsItem* physicsItem);

	virtual FVector CalculateImpulseDir(const FHitResult& traceResult) const override;
};
