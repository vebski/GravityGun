// Dawid Niemiec

#pragma once

#include "GravityGun.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGInventoryComponent.generated.h"

class AGGWeaponBase;
class AGGCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(GravityGun), meta=(BlueprintSpawnableComponent) )
class GRAVITYGUN_API UGGInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentWeaponIndex = INDEX_NONE;

	// All owned weapons are spawned at all times
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TArray<AGGWeaponBase*> OwnedWeapons;

	// Templates for weapons spawned when invontry is created
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TArray<TSubclassOf<AGGWeaponBase>> PresetWeaponTemplates;

	UGGInventoryComponent();

	virtual void BeginPlay() override;

public:	

	void SelectWeaponByIndex(const int32 weaponIndex);

	void SelectNextWeapon();

	void SelectPreviousWeapon();

	UFUNCTION(BlueprintCallable)
	AGGWeaponBase* GetCurrentWeapon() const;

	GG_FORCEINLINE int32 GetCurrentWeaponIndex() const
	{
		return CurrentWeaponIndex;
	}

	AGGCharacter* GetInventoryOwner() const;

};
