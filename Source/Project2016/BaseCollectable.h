// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseCollectable.generated.h"

class AC_Bowl;

UENUM(BlueprintType)
enum class ETimeEnum : uint8 {
	VE_None			UMETA(DisplayName = "None"),
	VE_Day			UMETA(DisplayName = "Day"),
	VE_Night		UMETA(DisplayName = "Night"),
	VE_Day_Broken	UMETA(DisplayName = "Day Broken"),
	VE_Night_Broken UMETA(DisplayName = "Night Broken")
};

UCLASS()
class PROJECT2016_API ABaseCollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCollectable();

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool enabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		UTexture* itemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		uint8 animationType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FName supposedBowlTag;

	UPROPERTY(VisibleDefaultsOnly, Category = "Private")
		APlayerController* playerControllerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eventually cut")
		bool bowl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eventually cut")
		bool flower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		TSubclassOf<ABaseCollectable> supposedRepairObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		USoundBase* c_sCollect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		USoundBase* c_sDrop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		FName c_supposedObjectTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		bool m_broken = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
		ETimeEnum m_supposedtimeenum;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, Category = "Default")
		class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Default")
		class USphereComponent* m_outlinesphere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Default")
		class UStaticMeshComponent *StaticMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Default")
		class UStaticMeshComponent *C_BrokenMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetMeshVisibility(bool visible);

	void CollectObject();

	//Functions	
	UFUNCTION(BlueprintCallable, Category = "ItemFunction")
		virtual void c_CollectItem();

	UFUNCTION(BlueprintCallable, Category = "ItemFunction")
		virtual void c_newDropItem();

	UFUNCTION(BlueprintCallable, Category = "Overlap")
		virtual void OnOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Overlap")
		virtual void OnEndOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category = "Overlap")
		virtual void OnOutline(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable, Category = "Overlap")
		virtual void OnEndOutline(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
