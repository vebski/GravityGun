// Dawid Niemiec

#include "GGProjectileMoving.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"


FName AGGProjectileMoving::ProjectileCollisionComponentName("ProjectileCollisionComponent");

AGGProjectileMoving::AGGProjectileMoving()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(AGGProjectileMoving::ProjectileCollisionComponentName);
	SetRootComponent(CollisionComponent);
	// #TODO_Dawid setup collision profile

	// #TODO_Dawid bindings to collision component
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
}
