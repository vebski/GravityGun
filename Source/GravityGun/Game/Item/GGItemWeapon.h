// Dawid Niemiec

#pragma once

#include "CoreMinimal.h"
#include "Game/Item/GGItemBase.h"
#include "GGItemWeapon.generated.h"

class AGGWeaponBase;

UCLASS()
class GRAVITYGUN_API AGGItemWeapon : public AGGItemBase
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TSubclassOf<AGGWeaponBase> WeaponTemplate;
	
	virtual void BeginPlay() override;

	
public:
	
};
