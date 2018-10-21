// Dawid Niemiec

#pragma once

#include "CoreMinimal.h"
#include "Game/Projectile/GGProjectileBase.h"
#include "GGProjectileMoving.generated.h"

class UProjectileMovementComponent;
class USphereCollisionComponent;
class USphereComponent;

/**
* Used for projectiles using "ProjectilveMovementComponent"
* These projectiles usually have a collider and take "time" to travel
*/
UCLASS()
class GRAVITYGUN_API AGGProjectileMoving : public AGGProjectileBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	static FName ProjectileCollisionComponentName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	USphereComponent* CollisionComponent = nullptr;
	
	AGGProjectileMoving();

public:
	
};
