// Dawid Niemiec

#include "GGProjectileBase.h"
#include "../Weapon/GGWeaponBase.h"


// Sets default values
AGGProjectileBase::AGGProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Fallback lifespan
	InitialLifeSpan = 30.0f;
}

// Called when the game starts or when spawned
void AGGProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGGProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGGProjectileBase::InitializeProjectile(AGGWeaponBase* owningWeapon)
{
	check(owningWeapon != nullptr); // every projectile needs owning weapon!
	OwningWeapon = owningWeapon;
}

void AGGProjectileBase::DestroyProjectile()
{
	Destroy();
}