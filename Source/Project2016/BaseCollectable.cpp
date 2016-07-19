// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_PlayerController.h"
#include "BaseCollectable.h"
#include "C_Bowl.h"

// Sets default values
ABaseCollectable::ABaseCollectable()
{
	//Initialize Mesh Components
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collect Sphere"));
	m_outlinesphere = CreateDefaultSubobject<USphereComponent>(TEXT("Outline Sphere"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh"));
	C_BrokenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("C_BrokenMesh"));
	RootComponent = CapsuleComponent;
	C_BrokenMesh->SetupAttachment(RootComponent);
	SphereComponent->SetupAttachment(RootComponent);
	m_outlinesphere->SetupAttachment(RootComponent);
	StaticMeshComponent->SetupAttachment(RootComponent);

	//Delegate On Overlap Events
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseCollectable::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseCollectable::OnEndOverlap);

	m_outlinesphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseCollectable::OnOutline);
	m_outlinesphere->OnComponentEndOverlap.AddDynamic(this, &ABaseCollectable::OnEndOutline);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Enables Player to Interact with the object
void ABaseCollectable::OnOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this)
		return;

	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {

		if ((m_supposedtimeenum == ETimeEnum::VE_Day && !tempController->currentTime) ||
			(m_supposedtimeenum == ETimeEnum::VE_Night && tempController->currentTime) ||
			(m_supposedtimeenum == ETimeEnum::VE_Day_Broken && tempController->currentTime) ||
			(m_supposedtimeenum == ETimeEnum::VE_Night_Broken && !tempController->currentTime) ||
			 m_supposedtimeenum == ETimeEnum::VE_None) {

			tempController->c_TempInventory = this;
			if (tempController->c_Inventory != nullptr)
				tempController->bCanInteract = false;
		}
	}
}

// Disables Player interaction with the object
void ABaseCollectable::OnEndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this)
		return;

	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
		tempController->c_TempInventory = nullptr;
		tempController->bCanInteract = true;
	}
}

// Enables outline for the object
void ABaseCollectable::OnOutline(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this)
		return;

	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
		if(StaticMeshComponent != nullptr)
			StaticMeshComponent->SetRenderCustomDepth(true);

		if (C_BrokenMesh != nullptr)
			C_BrokenMesh->SetRenderCustomDepth(true);
	}
}

// Disables outline for the object
void ABaseCollectable::OnEndOutline(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this)
		return;

	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
		if (StaticMeshComponent != nullptr)
			StaticMeshComponent->SetRenderCustomDepth(false);

		if (C_BrokenMesh != nullptr)
			C_BrokenMesh->SetRenderCustomDepth(false);
	}
}

// Called when the game starts or when spawned
void ABaseCollectable::BeginPlay()
{
	Super::BeginPlay();

	m_charref = Cast<AC_MainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!m_charref->IsValidLowLevel())
		m_animationType = 99;
}

// Called every frame
void ABaseCollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Enable / Disable Object
	if (!m_enabled) {
		SetMeshVisibility(false);
		return;
	}

	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	switch (m_supposedtimeenum) {
	case ETimeEnum::VE_Day:
		if (!tempController->currentTime)
			SetMeshVisibility(true);
		else
			SetMeshVisibility(false);
		break;
	case ETimeEnum::VE_Night:
		if (tempController->currentTime)
			SetMeshVisibility(true);
		else
			SetMeshVisibility(false);
		break;
	case ETimeEnum::VE_Day_Broken:
		if (!tempController->currentTime) {
			m_broken = true;
			SetMeshVisibility(false);
		}
		else {
			m_broken = false;
			SetMeshVisibility(true);
		}
		break;
	case ETimeEnum::VE_Night_Broken:
		if (tempController->currentTime) {
			m_broken = true;
			SetMeshVisibility(false);
		}
		else {
			m_broken = false;
			SetMeshVisibility(true);
		}
		break;
	case ETimeEnum::VE_None:
		SetMeshVisibility(true);
		break;
	default:
		SetMeshVisibility(false);
		break;
	}
}

void ABaseCollectable::SetMeshVisibility(bool visible)
{
	RootComponent->SetVisibility(visible, true);
	SetActorEnableCollision(visible);

	if (!m_enabled)
		return;

	if (C_BrokenMesh != nullptr) {
		RootComponent->SetVisibility(!m_broken, true);
		C_BrokenMesh->SetVisibility(m_broken, false);
	}
}

void ABaseCollectable::CollectObject()
{
	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	if (tempController->c_Inventory == nullptr) {
		m_enabled = false;
		SetMeshVisibility(false);
		tempController->c_Inventory = this;
		tempController->c_TempInventory = nullptr;
	}
}

void ABaseCollectable::c_newDropItem()
{
	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	AC_MainCharacter* tempCharacter = Cast<AC_MainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!tempCharacter->IsValidLowLevel())
		return;

	if (tempController->c_Inventory->m_sDrop->IsValidLowLevel())
		tempController->cPlaySound(tempController->c_Inventory->m_sDrop);
	else if (tempController->c_sDrop->IsValidLowLevel())
		tempController->cPlaySound(tempController->c_sDrop);

	tempController->c_Inventory->SetActorLocation(tempCharacter->m_sphereComponent->GetComponentLocation(), true);
	tempController->c_Inventory = nullptr;
	m_enabled = true;
}

void ABaseCollectable::c_CollectItem()
{
	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	//Play Sound
	if (tempController->c_TempInventory->m_sCollect->IsValidLowLevel())
		tempController->cPlaySound(tempController->c_TempInventory->m_sCollect);
	else if (tempController->c_sCollect->IsValidLowLevel())
		tempController->cPlaySound(tempController->c_sCollect);

	if (m_broken) {
		if (tempController->c_Inventory->IsValidLowLevel()) {
			if (tempController->c_Inventory->GetClass()->IsChildOf(m_supposedRepairObject)) {
				m_broken = false;
				tempController->c_Inventory = nullptr;
			}
		}
	}
	else {
		switch (m_supposedtimeenum) {
		case ETimeEnum::VE_Day: {
			if (!tempController->currentTime)
				CollectObject();
			break;
		}
		case ETimeEnum::VE_Night: {
			if (tempController->currentTime)
				CollectObject();
			break;
		}
		case ETimeEnum::VE_Day_Broken: {
			if (tempController->currentTime)
				CollectObject();
			break;
		}
		case ETimeEnum::VE_Night_Broken: {
			if (!tempController->currentTime)
				CollectObject();
			break;
		}
		case ETimeEnum::VE_None: {
			CollectObject();
			break;
		}
		default: {
			SetMeshVisibility(false);
			break;
		}
		}
	}
}