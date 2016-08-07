// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SaveAndLoad.h"
#include "GameFramework/GameMode.h"
#include "MGameMode.generated.h"

UENUM(BlueprintType)
enum class ESoundTypeEnum : uint8 {
	VE_Master			UMETA(DisplayName = "Master"),
	VE_Ambient			UMETA(DisplayName = "Ambient"),
	VE_SFX				UMETA(DisplayName = "SFX")
};

UCLASS()
class PROJECT2016_API AMGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float m_MasterVolume = 0.5f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float m_AmbientVolume = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float m_SFXVolume = 0.5f;

	UFUNCTION(BlueprintCallable, Category = Sound)
		void SetSoundClassVolume(USoundClass* TargetSoundClass, float NewVolume);
};
