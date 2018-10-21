// Dawid Niemiec

#include "GGPlayerController.h"

#include "Game/GGInventoryComponent.h"

AGGPlayerController::AGGPlayerController()
{
	InventoryComponent = CreateDefaultSubobject<UGGInventoryComponent>(TEXT("InventoryComponent"));


}
