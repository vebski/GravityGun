// Dawid Niemiec

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGWeaponBase.generated.h"

class USkeletalMeshComponent;
class UArrowComponent;

class AGGCharacter;
class AGGProjectileBase;

UCLASS(Abstract)
class GRAVITYGUN_API AGGWeaponBase : public AActor
{
	GENERATED_BODY()
	

protected:

	// Replacement for default UE4 root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* WeaponRootComponent = nullptr;

	// Used as position to fire projectiles from
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UArrowComponent* MuzzleComponent = nullptr;

	//////////////////////////////////////////////////////////////////////////
	// Weapon visuals

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals")
	USkeletalMeshComponent* WeaponMeshComponent = nullptr;
	
	//////////////////////////////////////////////////////////////////////////
	// Weapon Status

	UPROPERTY()
	AGGCharacter* OwningCharacter = nullptr;

	// Weapon is equipped after user selects it
	UPROPERTY()
	bool bIsEquipped = false;

	// Weapon is ready only when fully equipped
	UPROPERTY()
	bool bIsReady = false;

	UPROPERTY()
	bool bIsPrimaryFireActive = false;

	UPROPERTY()
	bool bIsSecondaryFireActive = false;
	
	UPROPERTY()
	float CurrentEquipCooldown = 0.0f;

	UPROPERTY()
	float CurrentPrimaryFirerateCooldown = 0.0f;

	UPROPERTY()
	float CurrentSecondaryFirerateCooldown = 0.0f;

	//////////////////////////////////////////////////////////////////////////
	// Weapon Config

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	TSubclassOf<AGGProjectileBase> PrimaryProjectileTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	TSubclassOf<AGGProjectileBase> SecondaryProjectileTemplate;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	float EquipDuration = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	bool bIsPrimarySingleFire = false;

	// Time between each shot | in sec 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	float PrimaryFirerateCooldown = 0.75f; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	bool bIsSecondarySingleFire = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
	float SecondaryFirerateCooldown = 0.5f;

	AGGWeaponBase();
	
	virtual void BeginPlay() override;

	virtual void UpdateWeapon(float deltaTime);

	virtual void PrimaryFire();

	virtual void SecondaryFire();

	virtual void ShowWeaponVisuals();

	virtual void HideWeaponVisuals();

	virtual void CompleteEquip();

	virtual void CompleteUnequop();

	virtual AGGProjectileBase* SpawnProjectile(TSubclassOf<AGGProjectileBase> projectileTemplate);

	virtual bool CanFirePrimary() const;

	virtual bool CanFireSecondary() const;

	virtual FTransform CalculateProjectileSpawnTransform(TSubclassOf<AGGProjectileBase> projectileTemplate) const;

public:	
	
	virtual void Tick(float deltaTime) override;

	// Called when we switch to the weapon (usually by inventory system)
	virtual void Equip();

	virtual void Unequip();

	UFUNCTION(BlueprintCallable)
	virtual void StartPrimaryFire();

	UFUNCTION(BlueprintCallable)
	virtual void StopPrimaryFire();
	
	UFUNCTION(BlueprintCallable)
	virtual void StartSecondaryFire();

	UFUNCTION(BlueprintCallable)
	virtual void StopSecondaryFire();

	// Can the weapon fire due to character movement and other character conditions
	virtual bool CanFire() const;

	void SetOwningCharacter(AGGCharacter* owningCharacter);

	AGGCharacter* GetOwningCharacter() const;

	UArrowComponent* GetMuzzleComponent() const;

};
