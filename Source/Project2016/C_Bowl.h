// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "C_MainCharacter.h"
#include "AudioMaster.h"
#include "C_PlayerController.h"
#include "GameFramework/Actor.h"
#include "C_Bowl.generated.h"

class ABaseCollectable;

UCLASS()
class PROJECT2016_API AC_Bowl : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_Bowl();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DefaultNotEditable")
		bool c_CanInteract = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool bowlExist = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DefaultNotEditable")
		bool c_solved;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		uint8 animationType = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		EAnimationEnum m_animationTypeEnum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		USoundBase* c_sPlaceObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		USoundBase* c_sTakeObject;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DefaultNotEditable")
		AC_PlayerController* pController_Ref;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		class UStaticMeshComponent *c_Bowl;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		class UStaticMeshComponent *c_BowlBroken;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		class UStaticMeshComponent *c_InsertedObject;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		class USkeletalMeshComponent *m_NormalMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		class USkeletalMeshComponent *m_BrokenMesh;

	UPROPERTY(VisibleAnywhere, Category = "Default")
		class USphereComponent* c_CollisionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TSubclassOf<ABaseCollectable> acceptedClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TSubclassOf<ABaseCollectable> acceptedClassRepair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		ABaseCollectable* c_slot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FName c_supposedObjectTag;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		class UAudioMaster* AudioMaster;

	AC_MainCharacter* m_charref;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	


	UFUNCTION(BlueprintCallable, Category = "ItemFunction")
		ABaseCollectable* InteractBowlObject(ABaseCollectable* object);

	UFUNCTION(BlueprintCallable, Category = "ItemFunction")
		virtual void RefreshSlot();

	UFUNCTION(BlueprintCallable, Category = "Overlap")
		virtual void OnOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Overlap")
		virtual void OnEndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};