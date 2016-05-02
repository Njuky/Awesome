// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "S_AI_Basic.generated.h"

UCLASS()
class PROJECT2016_API AS_AI_Basic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AS_AI_Basic();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		class UStaticMeshComponent *StaticMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Default")
		class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Default") bool active;
	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Default") AS_AI_Basic* nextActor;

	UFUNCTION(BlueprintCallable, Category = "AI Function") virtual void ActivateNextActor();

};
