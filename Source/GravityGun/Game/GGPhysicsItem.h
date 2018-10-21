// Dawid Niemiec

#pragma once

#include "GravityGun.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGPhysicsItem.generated.h"

UCLASS()
class GRAVITYGUN_API AGGPhysicsItem : public AActor
{
	GENERATED_BODY()
	

protected:

	// big items can be pushed/pulled but they can't be attached to weapons
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	bool bIsBigItem = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MainMeshComponent = nullptr;


	AGGPhysicsItem();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FBox GetPhysicsBounds() const;

	// Returns main component responsible for physics
	UPrimitiveComponent* GetMainComponent() const;
	
	bool IsBigItem(float maxSize) const;

};
