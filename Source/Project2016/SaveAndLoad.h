// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "C_MainCharacter.h"
#include "BaseCollectable.h"
#include "C_Bowl.h"
#include "GameFramework/Actor.h"
#include "SaveAndLoad.generated.h"

UCLASS()
class PROJECT2016_API ASaveAndLoad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASaveAndLoad();
private:
		bool m_saved = false;

		float m_waited = 0.0f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		float m_SaveCooldown = 10.0f;

	UPROPERTY(VisibleAnywhere, Category = "Default")
		class USphereComponent* m_CollisionSphere;

	// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	// Called every frame
		virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		virtual void SaveGame();
	
	UFUNCTION(BlueprintCallable, Category = "LoadGame")
		virtual void LoadGame();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		virtual void SaveSettings();

	UFUNCTION(BlueprintCallable, Category = "LoadGame")
		virtual void LoadSettings();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		virtual void SaveCollectable(ABaseCollectable *Object);

	UFUNCTION(BlueprintCallable, Category = "LoadGame")
		virtual void LoadCollectable(ABaseCollectable *Object);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		virtual void SaveBowl(AC_Bowl *Object);

	UFUNCTION(BlueprintCallable, Category = "LoadGame")
		virtual void LoadBowl(AC_Bowl *Object);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		virtual void SaveController();

	UFUNCTION(BlueprintCallable, Category = "LoadGame")
		virtual void LoadController();

	UFUNCTION(BlueprintCallable, Category = "Overlap")
		virtual void OnOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
