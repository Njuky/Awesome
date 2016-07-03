// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseCollectable.generated.h"

class AC_Bowl;

UCLASS()
class PROJECT2016_API ABaseCollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCollectable();

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool enabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		UTexture* itemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FName supposedBowlTag;

	UPROPERTY(VisibleDefaultsOnly, Category = "Private")
		APlayerController* playerControllerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool timeRelevant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool supposedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool broken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool bowl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool flower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool altar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		AC_Bowl* c_LastPlace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TSubclassOf<ABaseCollectable> supposedRepairObject;


	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, Category = "Default")
		class USphereComponent* SphereComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Default")
		class UStaticMeshComponent *StaticMeshComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void CollectObject();

	//Functions
	UFUNCTION(BlueprintCallable, Category = "ItemFunction")
		virtual void c_DropItem();
	
	UFUNCTION(BlueprintCallable, Category = "ItemFunction")
		virtual void c_CollectItem();
};
