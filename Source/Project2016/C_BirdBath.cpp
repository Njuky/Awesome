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

/*
void AC_BirdBath::Interact() {
	if (pController_Ref->IsValidLowLevel()) {
		//if (pController_Ref->currentTime == c_supposedTime) {
			if (pController_Ref->c_Inventory->IsValidLowLevel()) {
				//Insert Ball
				if (pController_Ref->c_Inventory->GetClass()->IsChildOf(acceptedClass) && !c_slot->IsValidLowLevel()) {
					c_InsertedObject->SetStaticMesh(pController_Ref->c_Inventory->StaticMeshComponent->StaticMesh);
					c_InsertedObject->SetMaterial(0, pController_Ref->c_Inventory->StaticMeshComponent->GetMaterial(0));
					c_InsertedObject->SetVisibility(true, false);
					pController_Ref->c_Inventory->flower = true;
					c_slot = pController_Ref->c_Inventory;
					pController_Ref->c_Inventory = NULL;
					if (c_slot->supposedBowlTag == c_supposedObjectTag) {
						c_solved = true;
					}
				}//Insert Berry
				else if (pController_Ref->c_Inventory->GetClass()->IsChildOf(acceptedClassBath) && !c_slotBath->IsValidLowLevel()) {
					c_InsertedObjectBath->SetVisibility(true, false);
					c_slotBath = pController_Ref->c_Inventory;
					pController_Ref->c_Inventory = NULL;
				}
				//Stone -> Smash Berry
				else if (pController_Ref->c_Inventory->GetClass()->IsChildOf(acceptedClassSmash) && c_slotBath->IsValidLowLevel()) {
					c_Bowl->SetVisibility(false, false);
					c_InsertedObjectBath->SetVisibility(false, false);
					c_BowlWater->SetVisibility(true, false);
					c_color = true;
					pController_Ref->c_Inventory = NULL;
				}
			}else {
				if (c_slot->IsValidLowLevel()) {
					pController_Ref->c_Inventory = c_slot;
					pController_Ref->c_Inventory->bowl = true;
					pController_Ref->c_Inventory->c_LastPlace = this;
					pController_Ref->c_Inventory->flower = false;
					c_InsertedObject->SetVisibility(false, false);
					c_slot = NULL;
					c_solved = false;
				}
			}
		//}
		else {
			if (pController_Ref->c_Inventory->GetClass()->IsChildOf(acceptedClassRepair)) {
				bowlExist = true;
				pController_Ref->c_Inventory = NULL;
			}
		}
	}
}*/