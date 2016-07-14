// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_BirdBath.h"

// Sets default values
AC_BirdBath::AC_BirdBath()
{
	c_BowlWater = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("c_BowlWater"));
	c_InsertedObjectBath = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("c_InsertedObjectBath"));
	c_BowlWater->SetupAttachment(RootComponent);
	c_InsertedObjectBath->SetupAttachment(RootComponent);
}

void AC_BirdBath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (pController_Ref->c_Inventory->IsValidLowLevel()) {
		if (pController_Ref->c_Inventory->GetClass()->IsChildOf(acceptedClass)) {
			testttt = true;
		}
	}
	if (pController_Ref->currentTime && !c_color) {
		c_Bowl->SetVisibility(true, false);
		c_BowlWater->SetVisibility(false, false);
	}
	else if (pController_Ref->currentTime && c_color) {
		c_Bowl->SetVisibility(false, false);
		c_BowlWater->SetVisibility(true, false);
	}else{
		c_Bowl->SetVisibility(false, false);
		c_BowlWater->SetVisibility(true, false);
	}

	if (c_CanInteract) {
		if (pController_Ref->WasInputKeyJustPressed(EKeys::F) || pController_Ref->WasInputKeyJustPressed(EKeys::Gamepad_DPad_Right)) {
			Interact();
		}
	}
}