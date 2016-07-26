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

	c_CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AC_Bowl::OnOverlap);
	c_CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AC_Bowl::OnEndOverlap);
}

// Enables Player to Interact with the object
void AC_Bowl::OnOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this)
		return;

	if (!pController_Ref->IsValidLowLevel())
		return;

	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {

		c_CanInteract = true;
		pController_Ref->bCanInteract = false;
		pController_Ref->c_BowlRef = this;
	}
}

// Disables Player interaction with the object
void AC_Bowl::OnEndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this)
		return;

	if (!pController_Ref->IsValidLowLevel())
		return;

	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
		c_CanInteract = false;
		pController_Ref->bCanInteract = true;
		pController_Ref->c_BowlRef = nullptr;
	}
}

// Called when the game starts or when spawned
void AC_Bowl::BeginPlay()
{
	Super::BeginPlay();
	pController_Ref = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	m_charref = Cast<AC_MainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (!c_slot == NULL) {
		c_InsertedObject->SetVisibility(true, false);
		c_InsertedObject->SetStaticMesh(c_slot->StaticMeshComponent->StaticMesh);
		c_InsertedObject->SetMaterial(0, c_slot->StaticMeshComponent->GetMaterial(0));
		if (c_slot->m_supposedBowlTag == c_supposedObjectTag)
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
		m_charref->m_animation = m_animationTypeEnum;
	else
		InteractBowl();

	
}

void AC_Bowl::InteractBowl() {
	if (!pController_Ref->IsValidLowLevel())
		return;

	if (bowlExist) {//place object
		if (pController_Ref->c_Inventory->IsValidLowLevel()) {
			if (pController_Ref->c_Inventory->GetClass()->IsChildOf(acceptedClass) && !c_slot->IsValidLowLevel()) {
				pController_Ref->c_Inventory->StaticMeshComponent->SetRenderCustomDepth(false);
				c_slot = pController_Ref->c_Inventory;
				pController_Ref->c_Inventory = NULL;
				RefreshSlot();

				if (c_slot->m_supposedBowlTag == c_supposedObjectTag)
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

void AC_Bowl::RefreshSlot() {
	if (c_slot->IsValidLowLevel()) {
		c_InsertedObject->SetStaticMesh(c_slot->StaticMeshComponent->StaticMesh);
		c_InsertedObject->SetMaterial(0, c_slot->StaticMeshComponent->GetMaterial(0));
		c_InsertedObject->SetVisibility(true, false);
		c_InsertedObject->SetRenderCustomDepth(false);
	}
	else
		c_InsertedObject->SetVisibility(false, false);
}