// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_PlayerController.h"
#include "C_Ball.h"
#include "C_Bowl.h"


AC_Ball::AC_Ball() {

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseCollectable::OnOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseCollectable::OnEndOverlap);

	m_outlinesphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseCollectable::OnOutline);
	m_outlinesphere->OnComponentEndOverlap.AddDynamic(this, &ABaseCollectable::OnEndOutline);
}