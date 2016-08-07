// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "SaveSettings.generated.h"

USTRUCT()
struct FAudioVolumeStruct {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
		float MasterMixVolume;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		float AmbientMixVolume;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		float SFXMixVolume;
};

UCLASS()
class PROJECT2016_API USaveSettings : public USaveGame
{
	GENERATED_BODY()
	
public:
		UPROPERTY(VisibleAnywhere, Category = Basic)
			FAudioVolumeStruct SaveAudioVolume;
	
		UPROPERTY(VisibleAnywhere, Category = Basic)
			FString SaveSlotName;

		UPROPERTY(VisibleAnywhere, Category = Basic)
			uint32 UserIndex;

		USaveSettings();
};
