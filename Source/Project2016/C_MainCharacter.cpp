// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_MainCharacter.h"


// Sets default values
AC_MainCharacter::AC_MainCharacter()
{
	m_sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Drop Location Sphere"));
	m_sphereComponent->SetupAttachment(RootComponent);

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_MainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_MainCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AC_MainCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

