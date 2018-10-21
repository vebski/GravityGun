// Dawid Niemiec

#pragma once

#include "GravityGun.h"

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GGGravityPullComponent.generated.h"

class AGGPhysicsItem;
class AGGWeaponBase;
class USceneComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYGUN_API UGGGravityPullComponent : public UPhysicsHandleComponent
{
	GENERATED_BODY()


protected:

	// #TODO_Dawid in gravity gun secondary mode attracts an item if there is none attracted, if there is an attracted item it drops it on the ground
	UPROPERTY(BlueprintReadOnly)
	AGGPhysicsItem* PulledItem = nullptr;

	// offset from camera for target based on camera position/dir
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	float TargetCameraOffset = 120.0f;

	// How far separated from PullTarget item can be, before it gets released
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	float ReleaseDist = 500.0f;

	// At what distance from target we accept that item reached it
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	float TargetReachedDist = 10.0f;

	UPROPERTY()
	bool bReachedTarget = false;

	UPROPERTY()
	USceneComponent* PullTargetComponent = nullptr;

	// cached access
	UPROPERTY()
	AGGWeaponBase* OwningWeapon = nullptr;

	UGGGravityPullComponent();

	virtual void UpdatePull(float deltaTime);

	virtual FVector UpdateTargetPosition(float deltaTime);

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void StartPullingItem(AGGPhysicsItem* physicsItem);
		
	virtual void StopPullingItem();

	void SetPullTargetComponent(USceneComponent* pullTargetComponent);

	GG_FORCEINLINE bool IsPullingItem() const
	{
		return PulledItem != nullptr;
	}

	bool CanPull() const;

	void SetOwningWeapon(AGGWeaponBase* owningWeapon);
};
