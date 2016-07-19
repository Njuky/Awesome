// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "C_MainCharacter.generated.h"

UENUM(BlueprintType)
enum class EAnimationEnum : uint8 {
	VE_Walk			UMETA(DisplayName = "Walk"),
	VE_InteractLow	UMETA(DisplayName = "Interact Low"),
	VE_InteractHigh UMETA(DisplayName = "Interact High")
};

UCLASS()
class PROJECT2016_API AC_MainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_MainCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool m_allowmovement = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		EAnimationEnum m_animation = EAnimationEnum::VE_Walk;

	UPROPERTY(VisibleAnywhere, Category = "Default")
		class USphereComponent* m_sphereComponent;
};
