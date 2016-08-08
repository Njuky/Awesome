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
	m_NormalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_NormalMesh"));
	m_BrokenMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_BrokenMesh"));
	AudioMaster = CreateDefaultSubobject<UAudioMaster>(TEXT("AudioMaster"));
	RootComponent = c_CollisionSphere;
	m_NormalMesh->SetupAttachment(RootComponent);
	m_BrokenMesh->SetupAttachment(RootComponent);
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
}


ABaseCollectable* AC_Bowl::InteractBowlObject(ABaseCollectable* object) {

	ABaseCollectable* returnValue = nullptr;

	if (bowlExist) {
		if (object->IsValidLowLevel()) {
			if (object->GetClass()->IsChildOf(acceptedClass) && !c_slot->IsValidLowLevel()) {
				c_slot = object;
				RefreshSlot();

				if (c_slot->m_supposedBowlTag == c_supposedObjectTag)
					c_solved = true;

				if (c_sPlaceObject != nullptr)
					AudioMaster->PlaySound(c_sPlaceObject);

				return nullptr;
			}
		}
		else {
			if (c_slot == nullptr)
				return nullptr;

			ABaseCollectable* returnValue = c_slot;
			c_slot = nullptr;
			c_solved = false;
			RefreshSlot();

			if (c_sTakeObject != nullptr)
				AudioMaster->PlaySound(c_sTakeObject);

			return returnValue;
		}
	}
	else {
		if (object->GetClass()->IsChildOf(acceptedClassRepair)) {
			bowlExist = true;

			if (c_sPlaceObject != nullptr)
				AudioMaster->PlaySound(c_sPlaceObject);

			return nullptr;
		}
	}
	return object;
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
