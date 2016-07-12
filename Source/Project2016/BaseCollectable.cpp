// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_PlayerController.h"
#include "BaseCollectable.h"
#include "C_Bowl.h"


// Sets default values
ABaseCollectable::ABaseCollectable()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh"));
	RootComponent = CapsuleComponent;
	SphereComponent->AttachParent = RootComponent;
	StaticMeshComponent->AttachParent = RootComponent;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCollectable::BeginPlay()
{
	Super::BeginPlay();

	if(SphereComponent == nullptr)
		SphereComponent->DestroyComponent();

	if (StaticMeshComponent == nullptr)
		StaticMeshComponent->DestroyComponent();	
}

// Called every frame
void ABaseCollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Set Actor Collision (on if enabled, off if disabled)
	SetActorEnableCollision(enabled);

	//Enable / Disable Object
	if (!enabled) {
		RootComponent->SetVisibility(false, true);
		SetActorEnableCollision(false);
		return;
	}

	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	if (timeRelevant) {
		if (tempController->currentTime == supposedTime) {
			RootComponent->SetVisibility(true, true);
			SetActorEnableCollision(true);
		}
		else {
			RootComponent->SetVisibility(false, true);
			SetActorEnableCollision(false);
		}
	}

	//if (flower) {
	//	RootComponent->SetVisibility(false, true);
	//	SetActorEnableCollision(false);
	//}

}

void ABaseCollectable::CollectObject()
{
	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	if (tempController->c_Inventory == NULL) {
		StaticMeshComponent->SetVisibility(false, true);
		SetActorEnableCollision(false);
		tempController->c_Inventory = this;
		enabled = false;
	}
}

void ABaseCollectable::c_DropItem()
{
	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	if (!bowl) {
		tempController->c_Inventory = NULL;
		RootComponent->SetVisibility(true, true);
		SetActorEnableCollision(true);
		enabled = true;

	}else if(bowl){
		c_LastPlace->c_slot = this;
		tempController->c_Inventory = NULL;
	}
}

void ABaseCollectable::c_newDropItem()
{
	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	tempController->c_Inventory->SetActorLocation(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(), true);
	tempController->c_Inventory = nullptr;
	enabled = true;
}

void ABaseCollectable::c_CollectItem()
{
	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	//Play Sound
	if (tempController->c_TempInventory->c_sCollect->IsValidLowLevel())
		tempController->cPlaySound(tempController->c_TempInventory->c_sCollect);
	else if (tempController->c_sCollect->IsValidLowLevel())
		tempController->cPlaySound(tempController->c_sCollect);

	if (broken) {
		if (tempController->c_Inventory->IsValidLowLevel()) {
			if (tempController->c_Inventory->GetClass()->IsChildOf(supposedRepairObject)) {
				broken = false;
				tempController->c_Inventory = NULL;
			}
		}
	}
	else {
		if (timeRelevant) {
			if (tempController->currentTime == supposedTime) 
				CollectObject();
		}
		else
			CollectObject();
	}
}