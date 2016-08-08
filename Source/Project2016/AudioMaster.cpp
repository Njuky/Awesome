// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "AudioMaster.h"


// Sets default values for this component's properties
UAudioMaster::UAudioMaster()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAudioMaster::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAudioMaster::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UAudioMaster::PlaySound(USoundBase* Sound)
{
	UGameplayStatics::PlaySound2D(GetWorld(), Sound, Sound->GetSoundClass()->Properties.Volume, 1, 0);
}

