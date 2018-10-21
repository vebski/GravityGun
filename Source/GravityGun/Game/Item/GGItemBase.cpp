// Dawid Niemiec

#include "GGItemBase.h"


// Sets default values
AGGItemBase::AGGItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGGItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGGItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

