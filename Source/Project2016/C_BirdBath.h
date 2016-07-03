// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "C_Bowl.h"
#include "C_BirdBath.generated.h"

class ABaseCollectable;

UCLASS()
class PROJECT2016_API AC_BirdBath : public AC_Bowl
{
	GENERATED_BODY()

	
public:
	AC_BirdBath();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool testttt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool c_color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	bool c_supposedTime;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
	class UStaticMeshComponent *c_InsertedObjectBath;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
	class UStaticMeshComponent *c_BowlWater;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TSubclassOf<ABaseCollectable> acceptedClassBath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	TSubclassOf<ABaseCollectable> acceptedClassSmash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	ABaseCollectable* c_slotBath;
	
//	UFUNCTION(BlueprintCallable, Category = "ItemFunction")
//	virtual void Interact();
};
