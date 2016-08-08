// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AudioMaster.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT2016_API UAudioMaster : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAudioMaster();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		// Plays a sound
	UFUNCTION(BlueprintCallable, Category = "PlaySound")
		void PlaySound(USoundBase* Sound);
	
};
