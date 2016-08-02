// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCollectable.h"
#include "C_MainCharacter.h"
#include "GameFramework/PlayerController.h"
#include "C_PlayerController.generated.h"

class AC_Bowl;

UENUM(BlueprintType)
enum class EInteractEnum : uint8 {
	VE_Collect		UMETA(DisplayName = "Collect Item"),
	VE_Drop			UMETA(DisplayName = "Drop Item"),
	VE_Interact		UMETA(DisplayName = "Interact Bowl"),
	VE_All			UMETA(DisplayName = "Check All")
};

UCLASS()
class PROJECT2016_API AC_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Variables
	//Dissolve
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DissolveVariables")
		bool timeWalk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DissolveVariables")
		bool currentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DissolveVariables")
		float dissolve = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DissolveVariables")
		TArray<AStaticMeshActor*> pastDissolveObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DissolveVariables")
		TArray<AStaticMeshActor*> futureDissolveObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DissolveVariables")
		TArray<APointLight*> pointLights;

	//ChangeColor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeColor")
		FLinearColor baseColorMatTree_Night;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeColor")
		FLinearColor fresnelColorMatTree_Night;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeColor")
		FLinearColor brushColorMatTree_Night;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeColor")
		FLinearColor baseColorWaveTree_Night;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeColor")
		FLinearColor baseColorMatBush_Night;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeColor")
		FLinearColor fresnelColorMatBush_Night;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeColor")
		FLinearColor brushColorMatBush_Night;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeColor")
		FLinearColor baseColorWaveBush_Night;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeColor")
		float waveEmissiveTree = 40.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeColor")
		float waveSize = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeColor")
		float waveSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChangeColor")
		float waveEmissiveBush = 5.0f;

	//Lightning
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
		APostProcessVolume* dayPPV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
		APostProcessVolume* nightPPV;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightning")
		ADirectionalLight* ambLight;

	//Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		TArray<AAmbientSound*> ambSoundDay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		TArray<AAmbientSound*> ambSoundNight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
		float fSoundVolume = 1.0f;

	//TimewalkDefault
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkDefault")
		bool init;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkDefault")
		bool buttonPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkDefault")
		bool canTimewalk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkDefault")
		bool timeChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkDefault")
		float timeButtonPressed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkDefault")
		float timewalkDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkDefault")
		float timewalkInitTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkDefault")
		float timewalkRunTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkDefault")
		int32 count = 0;

	//TimewalkEffect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkEffect")
		float line;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkEffect")
		float opacity = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkEffect")
		float colorgrading = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkEffect")
		float minBright = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkEffect")
		float alpha = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkEffect")
		float oldAlpha = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkEffect")
		float alphaRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimewalkEffect")
		FLinearColor sceneColor;

	//Default
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool bCanInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		uint8 animationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		AC_Bowl* c_BowlRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		ABaseCollectable* c_Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		ABaseCollectable* c_TempInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		USoundBase* c_sCollect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		USoundBase* c_sDrop;

	AC_MainCharacter* m_charref;

	//Functions
	
	void SetupInputComponent();
	void Interact();

	UFUNCTION(BlueprintCallable, Category = "TimewalkDefault")
	bool UpdateAlpha(float DeltaTime, float runTime);

	UFUNCTION(BlueprintCallable, Category = "TimewalkDefault")
		void HandleItem(EInteractEnum interactEnum);

	UFUNCTION(BlueprintCallable, Category = "TimewalkDefault")
		void PlayerOverlapBegin(AActor* other);

	UFUNCTION(BlueprintCallable, Category = "TimewalkDefault")
		void PlayerOverlapEnd(AActor* other);

	UFUNCTION(BlueprintCallable, Category = "Default")
		void cPlaySound(USoundBase* sound);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
};