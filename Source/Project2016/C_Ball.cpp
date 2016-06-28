// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_PlayerController.h"
#include "C_Snail.h"
#include "C_Ball.h"
#include "C_Bowl.h"


AC_Ball::AC_Ball() {
	C_BrokenMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("C_BrokenMesh"));
	C_BrokenMesh->AttachParent = RootComponent;
}

void AC_Ball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (enabled) {
		if (timeRelevant) {
			AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			if (tempController->currentTime == supposedTime) {
				broken = false;
			}else{
				broken = true;
			}
		}if (broken) {
			C_BrokenMesh->SetVisibility(true, false);
			StaticMeshComponent->SetVisibility(false, false);
		}else{
			C_BrokenMesh->SetVisibility(false, false);
			StaticMeshComponent->SetVisibility(true, false);
		}
	}
}

//override collect function of parent class
void AC_Ball::c_CollectItem()
{
	if (enabled) {
		AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (broken) {
			if (tempController->c_Inventory->IsValidLowLevel()) {
				if (tempController->c_Inventory->GetClass()->IsChildOf(AC_Snail::StaticClass()) && snail) {
					broken = false;
					tempController->c_Inventory = NULL;
				}
			}
		}else {
			CollectObject();
		}
	}
}

void AC_Ball::c_DropItem() {
	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (c_LastPlace->IsValidLowLevel()) {
		c_LastPlace->Interact();
		tempController->c_Inventory = NULL;
	}
	else {
		tempController->c_Inventory = NULL;
		RootComponent->SetVisibility(true, true);
		SetActorEnableCollision(true);
		enabled = true;
	}
}