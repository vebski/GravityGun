// Dawid Niemiec

#pragma once

#include "CoreMinimal.h"
#include "Game/Projectile/Traced/GGProjectileTraced.h"
#include "Curves/CurveFloat.h"
#include "GGProjectileGravityBeam.generated.h"


UCLASS()
class GRAVITYGUN_API AGGProjectileGravityBeam : public AGGProjectileTraced
{
	GENERATED_BODY()
	
protected:

	// How much velocity this trace will apply to impacted actors
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	float ImpulseForce = 3000.0f;

	// ImpulesForce is scaled by this cuve mapped onto TraceLength
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	UCurveFloat* ForceScaling = nullptr;

	virtual void ProcessHits(const TArray<FHitResult>& traceResults) override;

	virtual float CalculateForce(const FVector& targetPos) const;

	virtual FVector CalculateImpulseDir(const FHitResult& traceResult) const;

};
