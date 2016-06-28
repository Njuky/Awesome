// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCollectable.h"
#include "C_Ball.generated.h"

UCLASS()
class PROJECT2016_API AC_Ball : public ABaseCollectable
{
	GENERATED_BODY()
public:
	AC_Ball();

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
	class UStaticMeshComponent *C_BrokenMesh;

	UFUNCTION(BlueprintCallable, Category = "ItemFunction")
		virtual void c_DropItem();		
};
