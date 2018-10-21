// Dawid Niemiec

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GGPlayerController.generated.h"

class UGGInventoryComponent;

UCLASS()
class GRAVITYGUN_API AGGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	UGGInventoryComponent* InventoryComponent = nullptr;

	AGGPlayerController();

public:
	
	
};
