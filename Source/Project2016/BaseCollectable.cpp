// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_PlayerController.h"
#include "BaseCollectable.h"


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
	
}

// Called every frame
void ABaseCollectable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//Set Actor Collision (on if enabled, off if disabled)
	SetActorEnableCollision(enabled);

	//Enable / Disable Object
	if (enabled) {
		AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if(timeRelevant){
			if (tempController->currentTime == supposedTime) {
				SphereComponent->SetVisibility(true, true);
				SetActorEnableCollision(true);
			}else{
				SphereComponent->SetVisibility(false, true);
				SetActorEnableCollision(false);
			}
		}
	}else {
		SphereComponent->SetVisibility(false, true);
		SetActorEnableCollision(false);
	}	
}

void ABaseCollectable::CollectObject()
{
	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
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
	tempController->c_Inventory = NULL;
	RootComponent->SetVisibility(true, true);
	SetActorEnableCollision(true);
	enabled = true;
}

void ABaseCollectable::c_CollectItem()
{
	if (timeRelevant) {
		AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (tempController->currentTime == supposedTime) {
			CollectObject();
		}
	}else{
		CollectObject();
	}
}