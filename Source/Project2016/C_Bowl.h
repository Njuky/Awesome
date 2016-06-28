// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "C_PlayerController.h"
#include "GameFramework/Actor.h"
#include "C_Bowl.generated.h"

class ABaseCollectable;

UCLASS()
class PROJECT2016_API AC_Bowl : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Bowl();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool c_CanInteract = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool bowlExist = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
		bool c_solved = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Default")
		AC_PlayerController* pController_Ref;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		class UStaticMeshComponent *c_Bowl;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		class UStaticMeshComponent *c_BowlBroken;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		class UStaticMeshComponent *c_InsertedObject;

	UPROPERTY(VisibleAnywhere, Category = "Default")
		class USphereComponent* c_CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TSubclassOf<ABaseCollectable> acceptedClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TSubclassOf<ABaseCollectable> acceptedClassRepair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		ABaseCollectable* c_slot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FName c_supposedObjectTag;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "ItemFunction")
		void Interact();
};