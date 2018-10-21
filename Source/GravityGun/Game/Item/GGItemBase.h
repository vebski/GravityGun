// Dawid Niemiec

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGItemBase.generated.h"

UCLASS()
class GRAVITYGUN_API AGGItemBase : public AActor
{
	GENERATED_BODY()
	
protected:

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals")
	//UStaticMeshComponent* ItemMeshComponent = nullptr;


	AGGItemBase();

	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
