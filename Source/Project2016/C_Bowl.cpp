// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_Bowl.h"


// Sets default values
AC_Bowl::AC_Bowl()
{
	c_CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("C_CollisionSphere"));
	c_Bowl = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("C_Bowl"));
	c_BowlBroken = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("C_BowlBroken"));
	c_InsertedObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("C_InsertedObject"));
	RootComponent = c_CollisionSphere;
	c_Bowl->SetupAttachment(RootComponent);
	c_BowlBroken->SetupAttachment(RootComponent);
	c_InsertedObject->SetupAttachment(RootComponent);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AC_Bowl::BeginPlay()
{
	Super::BeginPlay();
	pController_Ref = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!c_slot == NULL) {
		c_InsertedObject->SetVisibility(true, false);
		c_InsertedObject->SetStaticMesh(c_slot->StaticMeshComponent->StaticMesh);
		c_InsertedObject->SetMaterial(0, c_slot->StaticMeshComponent->GetMaterial(0));
		if (c_slot->supposedBowlTag == c_supposedObjectTag)
			c_solved = true;
	}
	else {
		c_InsertedObject->SetVisibility(false, false);
	}
}

// Called every frame
void AC_Bowl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bowlExist) {
		c_Bowl->SetVisibility(true, false);
		c_BowlBroken->SetVisibility(false, false);
	}
	else {
		c_Bowl->SetVisibility(false, false);
		c_BowlBroken->SetVisibility(true, false);
	}

	if (c_CanInteract) {
		if (pController_Ref->WasInputKeyJustPressed(EKeys::F) || pController_Ref->WasInputKeyJustPressed(EKeys::Gamepad_FaceButton_Right)) {
			Interact();
		}
	}
}

void AC_Bowl::Interact() {
	if (!pController_Ref->IsValidLowLevel()) 
		return;
	
	if (pController_Ref->c_BowlRef->IsValidLowLevel())
		pController_Ref->animationType = animationType;
	else
		InteractBowl();

	
}

void AC_Bowl::InteractBowl() {
	if (!pController_Ref->IsValidLowLevel())
		return;

	if (bowlExist) {//place object
		if (pController_Ref->c_Inventory->IsValidLowLevel()) {
			if (pController_Ref->c_Inventory->GetClass()->IsChildOf(acceptedClass) && !c_slot->IsValidLowLevel()) {
				c_InsertedObject->SetStaticMesh(pController_Ref->c_Inventory->StaticMeshComponent->StaticMesh);
				c_InsertedObject->SetMaterial(0, pController_Ref->c_Inventory->StaticMeshComponent->GetMaterial(0));
				c_InsertedObject->SetVisibility(true, false);
				pController_Ref->c_Inventory->flower = true; // WTF ?
				c_slot = pController_Ref->c_Inventory;
				pController_Ref->c_Inventory = NULL;

				if (c_slot->supposedBowlTag == c_supposedObjectTag)
					c_solved = true;

				if (c_sPlaceObject->IsValidLowLevel())
					pController_Ref->cPlaySound(c_sPlaceObject);
			}
		}
		else {
			if (c_slot == nullptr)
				return;

			if (c_slot->IsValidLowLevel()) {
				pController_Ref->c_Inventory = c_slot;
				pController_Ref->c_Inventory->bowl = true; // WTF ?
//				pController_Ref->c_Inventory->c_LastPlace = this;
				pController_Ref->c_Inventory->flower = false;
				c_InsertedObject->SetVisibility(false, false);
				c_slot = NULL;
				c_solved = false;

				if (c_sPlaceObject->IsValidLowLevel())
					pController_Ref->cPlaySound(c_sTakeObject);
			}
		}
	}
	else {
		if (pController_Ref->c_Inventory->GetClass()->IsChildOf(acceptedClassRepair)) {
			bowlExist = true;
			pController_Ref->c_Inventory = NULL;

			if (c_sPlaceObject->IsValidLowLevel())
				pController_Ref->cPlaySound(c_sPlaceObject);
		}
	}
}

