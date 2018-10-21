// Dawid Niemiec

#include "GGProjectileGravityBeam.h"
#include "DrawDebugHelpers.h"
#include "Game/GGPhysicsItem.h"
#include "Components/PrimitiveComponent.h"
#include "Curves/CurveFloat.h"




void AGGProjectileGravityBeam::ProcessHits(const TArray<FHitResult>& traceResults)
{
	if (traceResults.Num() > 0)
	{
		for (int32 tr = 0; tr < traceResults.Num(); ++tr)
		{
			DrawDebugSphere(GetWorld(), traceResults[tr].ImpactPoint, 10.0f, 6, FColor::Green, false, 3.0f, 0, 5.0f);
		}

		// get the blocking hit and apply impulse to it if actor is physics item
		const FHitResult& blockingHit = traceResults.Last();
		if (traceResults.Last().bBlockingHit && blockingHit.Actor.Get() != nullptr)
		{
			AGGPhysicsItem* blockingActor = Cast<AGGPhysicsItem>(blockingHit.Actor.Get());
			if (blockingActor != nullptr)
			{
				const FVector impluseDir = (blockingHit.ImpactNormal * -1.0f) *  CalculateForce(blockingHit.ImpactPoint);

				// #TODO_Dawid we should adjust the dir to push the object away from player in more predictable and "straight" line, currently its too random due to impact normal

				blockingActor->GetMainComponent()->AddImpulseAtLocation(impluseDir, blockingHit.ImpactPoint);
			}
		}
	}

	DestroyProjectile();
}

float AGGProjectileGravityBeam::CalculateForce(const FVector& targetPos) const
{
	float force = ImpulseForce;
	// calculate distance scaling based on the curve
	if (ForceScaling != nullptr)
	{
		const float dist = FVector::Dist(GetActorLocation(), targetPos);

		// map distance to 0.0 -> 1.0 range (we use normalized curves)
		const float t = FMath::GetMappedRangeValueClamped(FVector2D(0.0f, TraceLength), FVector2D(0.0f, 1.0f), dist);
		force = force * ForceScaling->GetFloatValue(t);
	}

	return force;
}
