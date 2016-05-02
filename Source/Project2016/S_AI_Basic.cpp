// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "S_AI_Basic.h"


// Sets default values
AS_AI_Basic::AS_AI_Basic()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = CapsuleComponent;
	StaticMeshComponent->AttachParent = RootComponent;
	SkeletalMeshComponent->AttachParent = RootComponent;
	SphereComponent->AttachParent = RootComponent;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AS_AI_Basic::BeginPlay()
{
	Super::BeginPlay();
	if (!active) {
		if (!StaticMeshComponent == NULL)
			StaticMeshComponent->SetVisibility(false, false);
		if (!SkeletalMeshComponent == NULL)
			SkeletalMeshComponent->SetVisibility(false, false);
	}else{
		if (!StaticMeshComponent == NULL)
			StaticMeshComponent->SetVisibility(true, false);
		if (!SkeletalMeshComponent == NULL)
			SkeletalMeshComponent->SetVisibility(true, false);
	}
	
}

// Called every frame
void AS_AI_Basic::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (active) {
		if (!StaticMeshComponent == NULL)
			StaticMeshComponent->SetVisibility(true, false);
		if (!SkeletalMeshComponent == NULL)
			SkeletalMeshComponent->SetVisibility(true, false);
	}else{
	
	}
}

void AS_AI_Basic::ActivateNextActor() {
	nextActor->active = true;
}
