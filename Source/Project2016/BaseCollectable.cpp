// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_PlayerController.h"
#include "BaseCollectable.h"

// Sets default values
ABaseCollectable::ABaseCollectable()
{
	//Initialize Mesh Components
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collect Sphere"));
	m_outlinesphere = CreateDefaultSubobject<USphereComponent>(TEXT("Outline Sphere"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh"));
	m_NormalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("m_NormalMesh"));
	C_BrokenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("C_BrokenMesh"));
	AudioMaster = CreateDefaultSubobject<UAudioMaster>(TEXT("AudioMaster"));
	RootComponent = C_BrokenMesh;
	m_NormalMesh->SetupAttachment(RootComponent);
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

	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		m_playerCanCollect = true;
}

// Disables Player interaction with the object
void ABaseCollectable::OnEndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == this)
		return;

	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		m_playerCanCollect = false;
}

// Enables outline for the object
void ABaseCollectable::OnOutline(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor == this)
		return;

	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
		if(StaticMeshComponent != nullptr)
			StaticMeshComponent->SetRenderCustomDepth(true);

		if (m_NormalMesh != nullptr)
			m_NormalMesh->SetRenderCustomDepth(true);

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

		if (m_NormalMesh != nullptr)
			m_NormalMesh->SetRenderCustomDepth(false);

		if (C_BrokenMesh != nullptr)
			C_BrokenMesh->SetRenderCustomDepth(false);
	}
}


// Called when the game starts or when spawned
void ABaseCollectable::BeginPlay()
{
	Super::BeginPlay();
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
	if (tempController == nullptr)
		return;

	if (GetDistanceTo(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) <= 500.0f)
		tempController->c_TempInventory = this;

}

// Sets TempInventory if player begins Overlap
ABaseCollectable* ABaseCollectable::PlayerBeginOverlap(bool currentTime) {
	if (!m_playerCanCollect)
		return nullptr;

	if ((m_supposedtimeenum == ETimeEnum::VE_Day && !currentTime) ||
		(m_supposedtimeenum == ETimeEnum::VE_Night && currentTime) ||
		(m_supposedtimeenum == ETimeEnum::VE_Day_Broken && currentTime) ||
		(m_supposedtimeenum == ETimeEnum::VE_Night_Broken && !currentTime) ||
		 m_supposedtimeenum == ETimeEnum::VE_None) {

		return this;
	}

	return nullptr;
}

// Clears TempInventory if player ends Overlap
ABaseCollectable* ABaseCollectable::PlayerEndOverlap(ABaseCollectable* other) {

	if(m_playerCanCollect)
		return nullptr;

	if (!m_enabled)
		return nullptr;

	return other;
}

// Checks if the current time is same as the object supposed time
void ABaseCollectable::CheckTime(bool currentTime) {
	switch (m_supposedtimeenum) {
	case ETimeEnum::VE_Day:
		if (!currentTime)
			SetMeshVisibility(true);
		else
			SetMeshVisibility(false);
		break;
	case ETimeEnum::VE_Night:
		if (currentTime)
			SetMeshVisibility(true);
		else
			SetMeshVisibility(false);
		break;
	case ETimeEnum::VE_Day_Broken:
		if (!currentTime) {
			m_broken = true;
			SetMeshVisibility(false);
		}
		else {
			m_broken = false;
			SetMeshVisibility(true);
		}
		break;
	case ETimeEnum::VE_Night_Broken:
		if (currentTime) {
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

// Sets the Object visible / invisible
void ABaseCollectable::SetMeshVisibility(bool visible)
{
	RootComponent->SetVisibility(visible, true);

	if (StaticMeshComponent != nullptr)
		StaticMeshComponent->SetVisibility(visible, false);

	if (m_NormalMesh != nullptr)
		m_NormalMesh->SetVisibility(visible, false);

	SetActorEnableCollision(visible);
	SetActorHiddenInGame(false);

	if (C_BrokenMesh == nullptr)
		SetActorHiddenInGame(true);

	if (!m_enabled)
		return;

	// If the actor has a broken Mesh, this will be set visible / invisible
	if (C_BrokenMesh != nullptr) {
		RootComponent->SetVisibility(!m_broken, true);
		C_BrokenMesh->SetVisibility(m_broken, false);
	}
}

// Returns the collected Object
ABaseCollectable* ABaseCollectable::CollectObject(ABaseCollectable* object)
{
	if (object == this) {
		m_enabled = false;
		SetMeshVisibility(false);

		if (m_sCollect != nullptr)
			AudioMaster->PlaySound(m_sCollect);
		return this;
	}

	return object;
}

// Enables the Object and clears inventory
ABaseCollectable* ABaseCollectable::DropItem(FVector location) {

	if (m_sDrop != nullptr)
		AudioMaster->PlaySound(m_sDrop);

	this->SetActorLocation(location, true);
	m_enabled = true;
	SetMeshVisibility(true);

	return nullptr;
}

// Starts interaction with the current item
ABaseCollectable* ABaseCollectable::InteractItem(ABaseCollectable* object, bool currentTime) {

	// Repairs item if the player has the fix object
	if (m_broken) {
		if (!object->IsValidLowLevel())
			return nullptr;

		if (object == this)
			return nullptr;

		if (object == m_repairObject) {
			if (m_sDrop != nullptr)
				AudioMaster->PlaySound(m_sDrop);

			m_broken = false;
			CheckTime(currentTime);
			return nullptr;
		}
	}
	else { // If object isn't broken, check time requirements
		switch (m_supposedtimeenum) {
		case ETimeEnum::VE_Day: {
			if (!currentTime)
				return CollectObject(object);
			break;
		}
		case ETimeEnum::VE_Night: {
			if (currentTime)
				return CollectObject(object);
			break;
		}
		case ETimeEnum::VE_Day_Broken: {
			if (currentTime)
				return CollectObject(object);
			break;
		}
		case ETimeEnum::VE_Night_Broken: {
			if (!currentTime)
				return CollectObject(object);
			break;
		}
		case ETimeEnum::VE_None: {
			return CollectObject(object);
			break;
		}
		default: {
			SetMeshVisibility(false);
			break;
		}
		}
	}
	return object;
}