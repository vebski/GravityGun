// Dawid Niemiec

#include "GGProjectileTraced.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Game/Weapon/GGWeaponBase.h"
#include "Game/Character/GGCharacter.h"



void AGGProjectileTraced::ProjectileTrace(TArray<FHitResult>& traceResults)
{
	const FVector traceStart = GetActorLocation();
	const FVector traceEnd = GetActorLocation() + (GetActorForwardVector() * TraceLength);

	FCollisionQueryParams queryParams;
	queryParams.bTraceComplex = true;
	
	// Add weapon and its owner to ignore list so we avoid their collision
	queryParams.AddIgnoredActor(OwningWeapon);
	queryParams.AddIgnoredActor(OwningWeapon->GetOwningCharacter());

	FHitResult hit;
	GetWorld()->LineTraceSingleByChannel(hit, traceStart, traceEnd, ECC_TRACE_PROJECTILE, queryParams);
	traceResults.Add(hit);
}

void AGGProjectileTraced::ProcessHits(const TArray<FHitResult>& traceResults)
{

}

void AGGProjectileTraced::InitializeProjectile(AGGWeaponBase* owningWeapon)
{
	Super::InitializeProjectile(owningWeapon);

	TArray<FHitResult> traceResults;

	ProjectileTrace(traceResults);
	ProcessHits(traceResults);
}
