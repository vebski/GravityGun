// Dawid Niemiec

#pragma once

#include "CoreMinimal.h"
#include "Game/Weapon/GGWeaponBase.h"
#include "GGWeaponGravityGun.generated.h"


class AGGPhysicsItem;
class UGGGravityPullComponent;

UCLASS()
class GRAVITYGUN_API AGGWeaponGravityGun : public AGGWeaponBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	USceneComponent* PullTargetComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay")
	UGGGravityPullComponent* GravityPullComponent = nullptr;

	AGGWeaponGravityGun();
	
	virtual void BeginPlay() override;

	virtual void PrimaryFire() override;

	virtual void SecondaryFire() override;

	virtual bool CheckTraceForProjectile(TSubclassOf<AGGProjectileBase> projectileTemplate) const;

public:
	
	virtual void PullPhysicsItem(AGGPhysicsItem* physicsItem);

	UFUNCTION(BlueprintCallable)
	virtual bool CanPushItem() const;

	UFUNCTION(BlueprintCallable)
	virtual bool CanPullItem() const;
};
