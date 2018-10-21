// Dawid Niemiec

#include "GGInventoryComponent.h"
#include "Weapon/GGWeaponBase.h"
#include "Core/GGPlayerController.h"
#include "Character/GGCharacter.h"



UGGInventoryComponent::UGGInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts
void UGGInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for(int32 w = 0; w < PresetWeaponTemplates.Num(); ++w)
	{ 
		AGGWeaponBase* newWeapon = GetWorld()->SpawnActor<AGGWeaponBase>(PresetWeaponTemplates[w]);
		newWeapon->SetOwningCharacter(GetInventoryOwner());


		OwnedWeapons.Add(newWeapon);
		
	}

	// equip first weapon if there is any
	if (OwnedWeapons.Num() > 0)
	{
		SelectWeaponByIndex(0);
	}
}

void UGGInventoryComponent::SelectWeaponByIndex(const int32 weaponIndex)
{
	if (OwnedWeapons.IsValidIndex(weaponIndex) == true) // if index is not valid we dont want to unequip current weapon
	{
		if (OwnedWeapons.IsValidIndex(CurrentWeaponIndex) == true)
		{
			OwnedWeapons[CurrentWeaponIndex]->Unequip();
		}

		CurrentWeaponIndex = weaponIndex;

		OwnedWeapons[CurrentWeaponIndex]->Equip();
	}

}

void UGGInventoryComponent::SelectNextWeapon()
{
	int32 nextWeaponIndex = (GetCurrentWeaponIndex() + 1) % OwnedWeapons.Num();
	SelectWeaponByIndex(nextWeaponIndex);
}

void UGGInventoryComponent::SelectPreviousWeapon()
{
	int32 previousWeaponIndex = GetCurrentWeaponIndex() - 1;
	if (previousWeaponIndex < 0)
	{
		previousWeaponIndex = OwnedWeapons.Num() - 1;
	}
	SelectWeaponByIndex(previousWeaponIndex);
}

AGGWeaponBase* UGGInventoryComponent::GetCurrentWeapon() const
{
	if (OwnedWeapons.IsValidIndex(GetCurrentWeaponIndex()) == true)
	{
		return OwnedWeapons[GetCurrentWeaponIndex()];
	}

	return nullptr;
}

AGGCharacter* UGGInventoryComponent::GetInventoryOwner() const
{
	AGGPlayerController* owningPC = Cast<AGGPlayerController>(GetOwner());
	if (ensure(owningPC != nullptr))
	{
		AGGCharacter* character = Cast<AGGCharacter>(owningPC->GetPawn());
		check(character != nullptr); // !! all characters owning inventory should parent from AGGCharacter type !!
		return character;
	}

	return nullptr;
}
