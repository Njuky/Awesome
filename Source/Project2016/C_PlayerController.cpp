// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_PlayerController.h"
#include "C_Bowl.h"

void AC_PlayerController::SetupInputComponent(){
	Super::SetupInputComponent();
	InputComponent->BindAction("Interact", IE_Pressed, this, &AC_PlayerController::Interact);
}

void AC_PlayerController::Interact() {
	if (!m_charref->IsValidLowLevel())
		return;

	// Drop Item
	if (c_Inventory->IsValidLowLevel() && bCanInteract) {
		m_charref->m_animation = EAnimationEnum::VE_InteractLow;
	}// Collect item
	else if (c_TempInventory->IsValidLowLevel() && !c_Inventory->IsValidLowLevel()) {
		m_charref->m_animation = c_TempInventory->m_animationTypeEnum;
	}// Interact Bowl
	else if (c_BowlRef->IsValidLowLevel()) {
		m_charref->m_animation = c_BowlRef->m_animationTypeEnum;
	}
}

//Updates alpha per tick
bool AC_PlayerController::UpdateAlpha(float DeltaTime, float runTime)
{
	bool returnBool = false;
	if (buttonPressed) {
		timeButtonPressed += DeltaTime;
		if (timeButtonPressed >= timewalkDelay && canTimewalk) {
			returnBool = true;
			if(!timeChanged)
				if (currentTime) {
					alpha = (timeButtonPressed - timewalkInitTime) / runTime;
					alpha = 1 - FMath::Clamp(alpha, 0.0f, 1.0f);
				}else{
					alpha = (timeButtonPressed - timewalkInitTime) / runTime;
					alpha = FMath::Clamp(alpha, 0.0f, 1.0f);
				}
		}
	}else{//Player released button early
		if (currentTime) {
			if (alpha != 1) {
				alpha += alphaRate;
				alpha = FMath::Clamp(alpha, 0.0f, 1.0f);
			}
		}else{
			if (alpha != 0) {
				alpha -= alphaRate;
				alpha = FMath::Clamp(alpha, 0.0f, 1.0f);
			}
		}
	}
	return returnBool;
}

void AC_PlayerController::cPlaySound(USoundBase* sound)
{
	if(sound->IsValidLowLevel())
		ClientPlaySound(sound, fSoundVolume, 1.0f);
}

// Called when the game starts or when spawned
void AC_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_charref = Cast<AC_MainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void AC_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_PlayerController::HandleItem(EInteractEnum interactEnum) {
	switch (interactEnum) {
	case EInteractEnum::VE_Collect:
		if (c_TempInventory->IsValidLowLevel()) {
			c_Inventory = c_TempInventory->InteractItem(c_TempInventory, currentTime);
			if (c_Inventory == c_TempInventory)
				c_TempInventory = nullptr;
		}
		break;
	case EInteractEnum::VE_Drop:
		if (c_Inventory->IsValidLowLevel())
			c_Inventory = c_Inventory->DropItem(m_charref->m_sphereComponent->GetComponentLocation());
		break;
	case EInteractEnum::VE_Interact:
		if (c_BowlRef->IsValidLowLevel())
			c_Inventory = c_BowlRef->InteractBowlObject(c_Inventory);
		break;
	case EInteractEnum::VE_All:
		if (c_TempInventory->IsValidLowLevel()) {
			if (c_Inventory->IsValidLowLevel())
				c_Inventory = c_TempInventory->InteractItem(c_Inventory, currentTime);
			else
				c_Inventory = c_TempInventory->InteractItem(c_TempInventory, currentTime);

			if (c_Inventory == c_TempInventory)
				c_TempInventory = nullptr;
		}
		else if (c_BowlRef->IsValidLowLevel())
			c_Inventory = c_BowlRef->InteractBowlObject(c_Inventory);
		else if (c_Inventory->IsValidLowLevel())
			c_Inventory = c_Inventory->DropItem(m_charref->m_sphereComponent->GetComponentLocation());
		break;
	}
}

void AC_PlayerController::PlayerOverlapBegin(AActor* other) {
	if (c_TempInventory->IsValidLowLevel())
		return;

	if (other->GetClass()->IsChildOf(ABaseCollectable::StaticClass())) {
		ABaseCollectable* tempObject = Cast<ABaseCollectable>(other);
		c_TempInventory = tempObject->PlayerBeginOverlap(currentTime);
	}
}

void AC_PlayerController::PlayerOverlapEnd(AActor* other) {
	if (other->GetClass()->IsChildOf(ABaseCollectable::StaticClass())) {
		ABaseCollectable* tempObject = Cast<ABaseCollectable>(other);
		c_TempInventory = tempObject->PlayerEndOverlap(c_TempInventory);
	}
}
