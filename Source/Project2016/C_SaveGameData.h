// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCollectable.h"
#include "GameFramework/SaveGame.h"
#include "C_SaveGameData.generated.h"

USTRUCT()
struct FSaveObjectStruct {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString Name;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FVector4 Position;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool Enabled;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool Broken;
};

USTRUCT()
struct FSaveBowlStruct {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString Name;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool BowlExist;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool Solved;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		ABaseCollectable* Slot;
};

USTRUCT()
struct FSaveControllerStruct {
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool CanTimewalk;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		bool CurrentTime;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		float Alpha;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		float OldAlpha;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		float Dissolve;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		float SoundVolume;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FVector4 Position;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FRotator Rotation;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		ADirectionalLight* Sun;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		ABaseCollectable* Inventory;
};

UCLASS()
class PROJECT2016_API UC_SaveGameData : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
		TArray<FSaveObjectStruct> SaveObjects;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		TArray<FSaveBowlStruct> SaveBowls;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FSaveControllerStruct SaveController;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	UC_SaveGameData();
};
