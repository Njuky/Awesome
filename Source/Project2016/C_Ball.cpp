// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_PlayerController.h"
#include "C_Snail.h"
#include "C_Ball.h"
#include "C_Bowl.h"


AC_Ball::AC_Ball() {

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseCollectable::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseCollectable::OnEndOverlap);

	m_outlinesphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseCollectable::OnOutline);
	m_outlinesphere->OnComponentEndOverlap.AddDynamic(this, &ABaseCollectable::OnEndOutline);
}
/*
//override collect function of parent class
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
*/