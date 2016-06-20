// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseCollectable.generated.h"

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
		FName supposedBowlTag;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		APlayerController* playerControllerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeBased")
		bool timeRelevant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeBased")
		bool supposedTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LastPlace")
		bool bowl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LastPlace")
		bool altar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, Category = "Default")
		class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		class UStaticMeshComponent *StaticMeshComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Functions
	UFUNCTION(BlueprintCallable, Category = "TimewalkDefault")
		void c_DropItem();
	
};
