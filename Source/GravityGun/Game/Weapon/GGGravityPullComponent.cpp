// Dawid Niemiec

#include "GGGravityPullComponent.h"
#include "../GGPhysicsItem.h"
#include "GGWeaponBase.h"
#include "Components/PrimitiveComponent.h"


UGGGravityPullComponent::UGGGravityPullComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;
}

void UGGGravityPullComponent::UpdatePull(float deltaTime)
{
	if (CanPull() == false)
	{
		StopPullingItem();
		return;
	}

	checkSlow(PulledItem != nullptr);

	FVector targetPos = UpdateTargetPosition(deltaTime);

	const float distToItem = FVector::Dist(targetPos, PulledItem->GetActorLocation());
	if (bReachedTarget == false)
	{
		// did not reach target yet for the first time, check it
		if (distToItem <= TargetReachedDist)
		{
			bReachedTarget = true;
		}
	}
	else
	{
		// check if item is too far from target and it doesn't make sense to pull it anymore
		if (distToItem > ReleaseDist)
		{
			StopPullingItem();
		}
	}
}

FVector UGGGravityPullComponent::UpdateTargetPosition(float deltaTime)
{
	// calculate targetPosition -> take into account the fact that center of object is not at the pivot
	FVector itemOrigin = FVector::ZeroVector;
	FVector itemExtent = FVector::ZeroVector;
	PulledItem->GetActorBounds(true, itemOrigin, itemExtent);

	FVector targetOffset = itemOrigin - PulledItem->GetActorLocation();
	FVector targetPos = PullTargetComponent->GetComponentLocation() - targetOffset;

	// update target for physics handle
	SetTargetLocationAndRotation(targetPos, PullTargetComponent->GetComponentRotation());

	return targetPos;
}

void UGGGravityPullComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsPullingItem() == true)
	{
		UpdatePull(DeltaTime);
	}
}

void UGGGravityPullComponent::StartPullingItem(AGGPhysicsItem* physicsItem)
{
	PulledItem = physicsItem;
	bReachedTarget = false;

	UPrimitiveComponent* componentToGrab = PulledItem->GetMainComponent();
	check(componentToGrab != nullptr);
	GrabComponentAtLocationWithRotation(componentToGrab, FName(), componentToGrab->GetComponentLocation(), componentToGrab->GetComponentRotation());
}

void UGGGravityPullComponent::StopPullingItem()
{
	if (PulledItem != nullptr)
	{
		ReleaseComponent();
	}

	bReachedTarget = false;
	PulledItem = nullptr;
}

void UGGGravityPullComponent::SetPullTargetComponent(USceneComponent* pullTargetComponent)
{
	PullTargetComponent = pullTargetComponent;
}

bool UGGGravityPullComponent::CanPull() const
{
	return	IsPullingItem() &&
			Cast<AGGWeaponBase>(GetOwner()) != nullptr && Cast<AGGWeaponBase>(GetOwner())->CanFire();
}

