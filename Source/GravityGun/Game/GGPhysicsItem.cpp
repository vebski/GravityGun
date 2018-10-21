// Dawid Niemiec

#include "GGPhysicsItem.h"
#include "Components/StaticMeshComponent.h"


AGGPhysicsItem::AGGPhysicsItem()
{
	PrimaryActorTick.bCanEverTick = true;

	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMeshComponent"));
	SetRootComponent(MainMeshComponent);
	MainMeshComponent->SetCollisionProfileName(FName("PhysicsActor"));
	MainMeshComponent->BodyInstance.bSimulatePhysics = true;
}

// Called when the game starts or when spawned
void AGGPhysicsItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGGPhysicsItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPrimitiveComponent* AGGPhysicsItem::GetMainComponent() const
{
	return MainMeshComponent;
}

bool AGGPhysicsItem::IsBigItem(float maxSize) const
{
	FVector origin = FVector::ZeroVector;
	FVector extent = FVector::ZeroVector;
	GetActorBounds(true, origin, extent);

	// check if x/y is greater then maxSize -> we don't really care about Z since it wont clip with any player meshes etc.
	return FMath::Max(extent.X, extent.Y) > maxSize;
}


