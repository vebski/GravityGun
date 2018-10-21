// Dawid Niemiec

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGProjectileBase.generated.h"

class AGGWeaponBase;

UCLASS()
class GRAVITYGUN_API AGGProjectileBase : public AActor
{
	GENERATED_BODY()

protected:

	// whenever this projectile should use screen center as its origin
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
	bool bSpawnAtViewCenter = false;

	UPROPERTY()
	AGGWeaponBase* OwningWeapon = nullptr;

	AGGProjectileBase();

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void InitializeProjectile(AGGWeaponBase* owningWeapon);

	virtual void DestroyProjectile();

	bool ShouldSpawnAtViewCenter() const
	{
		return bSpawnAtViewCenter;
	}

};
