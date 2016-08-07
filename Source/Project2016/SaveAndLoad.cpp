// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "MGameMode.h"
#include "SaveAndLoad.h"
#include "SaveSettings.h"
#include "C_SaveGameData.h"
#include "Kismet/GameplayStatics.h"

// -------------------------------------------------------------
//						BASE FUNCTIONS
// -------------------------------------------------------------

// Sets default values
ASaveAndLoad::ASaveAndLoad()
{
	m_CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("M_CollisionSphere"));
	m_CollisionSphere->SetupAttachment(RootComponent);
	m_CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASaveAndLoad::OnOverlap);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASaveAndLoad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASaveAndLoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_saved)
		if (m_waited >= m_SaveCooldown) {
			m_saved = false;
			m_waited = 0.0f;
		}
		else
			m_waited += DeltaTime;
}

// -------------------------------------------------------------
//						SAVEGAME FUNCTIONS
// -------------------------------------------------------------

void ASaveAndLoad::SaveGame() {
	for (TActorIterator<ABaseCollectable> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		ABaseCollectable *Object = *ActorItr;
		SaveCollectable(Object);
	}

	for (TActorIterator<AC_Bowl> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		AC_Bowl *Object = *ActorItr;
		SaveBowl(Object);
	}

	SaveController();
}

void ASaveAndLoad::LoadGame() {
	for (TActorIterator<ABaseCollectable> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		ABaseCollectable *Object = *ActorItr;
		LoadCollectable(Object);
	}

	for (TActorIterator<AC_Bowl> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		AC_Bowl *Object = *ActorItr;
		LoadBowl(Object);
	}

	LoadController();
}

// -------------------------------------------------------------
//						SETTINGS FUNCTIONS
// -------------------------------------------------------------

void ASaveAndLoad::SaveSettings() {
	USaveSettings* LoadGameInstance = Cast<USaveSettings>(UGameplayStatics::CreateSaveGameObject(USaveSettings::StaticClass()));
	LoadGameInstance = Cast<USaveSettings>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (!LoadGameInstance->IsValidLowLevel())
		LoadGameInstance = Cast<USaveSettings>(UGameplayStatics::CreateSaveGameObject(USaveSettings::StaticClass()));

	AMGameMode* tempGameMode = (AMGameMode*)GetWorld()->GetAuthGameMode();
	if (!tempGameMode->IsValidLowLevel())	
		return;

	LoadGameInstance->SaveAudioVolume.MasterMixVolume = tempGameMode->m_MasterVolume;
	LoadGameInstance->SaveAudioVolume.AmbientMixVolume = tempGameMode->m_AmbientVolume;
	LoadGameInstance->SaveAudioVolume.SFXMixVolume = tempGameMode->m_SFXVolume;

	UGameplayStatics::SaveGameToSlot(LoadGameInstance, LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex);

}

void ASaveAndLoad::LoadSettings() {
	USaveSettings* LoadGameInstance = Cast<USaveSettings>(UGameplayStatics::CreateSaveGameObject(USaveSettings::StaticClass()));
	LoadGameInstance = Cast<USaveSettings>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (!LoadGameInstance->IsValidLowLevel())
		return;

	AMGameMode* tempGameMode = Cast<AMGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!tempGameMode->IsValidLowLevel())
		return;

	tempGameMode->m_MasterVolume = LoadGameInstance->SaveAudioVolume.MasterMixVolume;
	tempGameMode->m_AmbientVolume = LoadGameInstance->SaveAudioVolume.AmbientMixVolume;
	tempGameMode->m_SFXVolume = LoadGameInstance->SaveAudioVolume.SFXMixVolume;
}

// -------------------------------------------------------------
//						OVERLAP FUNCTIONS
// -------------------------------------------------------------

// Enables Player to Interact with the object
void ASaveAndLoad::OnOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor == this)
		return;

	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) {
		if (!m_saved) {
			SaveGame();
			m_saved = true;
			m_waited = 0.0f;
		}
	}
}

// -------------------------------------------------------------
//					SAVE AND LOAD FUNCTIONS
// -------------------------------------------------------------

// -------------------------------------------------------------
//						BASE COLLECTABLE
// -------------------------------------------------------------

void ASaveAndLoad::SaveCollectable(ABaseCollectable *Object) {
	UC_SaveGameData* LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::CreateSaveGameObject(UC_SaveGameData::StaticClass()));
	LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (!LoadGameInstance->IsValidLowLevel())
		LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::CreateSaveGameObject(UC_SaveGameData::StaticClass()));

	bool bContains = false;

	// Checks if Object already exists in save file
	for (int i = 0; i < LoadGameInstance->SaveObjects.Num(); ++i) {
		if (LoadGameInstance->SaveObjects[i].Name == Object->GetName()) {
			LoadGameInstance->SaveObjects[i].Position = Object->GetActorLocation();
			LoadGameInstance->SaveObjects[i].Enabled = Object->m_enabled;
			LoadGameInstance->SaveObjects[i].Broken = Object->m_broken;
			bContains = true;
		}
	}// Saves Object into file if it doesnt exist
	if (!bContains && !Object->GetName().IsEmpty()) {
		FSaveObjectStruct SaveStruct;
		SaveStruct.Name = Object->GetName();
		SaveStruct.Position = Object->GetActorLocation();
		SaveStruct.Enabled = Object->m_enabled;
		SaveStruct.Broken = Object->m_broken;
		LoadGameInstance->SaveObjects.Add(SaveStruct);

		bContains = true;
	}
	UGameplayStatics::SaveGameToSlot(LoadGameInstance, LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex);
}

void ASaveAndLoad::LoadCollectable(ABaseCollectable *Object) {
	UC_SaveGameData* LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::CreateSaveGameObject(UC_SaveGameData::StaticClass()));
	LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (!LoadGameInstance->IsValidLowLevel())
		return;

	for (int i = 0; i < LoadGameInstance->SaveObjects.Num(); ++i) {
		if (LoadGameInstance->SaveObjects[i].Name == Object->GetName()) {
			Object->SetActorLocation(LoadGameInstance->SaveObjects[i].Position);
			Object->m_enabled = LoadGameInstance->SaveObjects[i].Enabled;
			Object->m_broken = LoadGameInstance->SaveObjects[i].Broken;
		}
	}
}

// -------------------------------------------------------------
//						BOWL
// -------------------------------------------------------------

void ASaveAndLoad::SaveBowl(AC_Bowl *Object) {
	UC_SaveGameData* LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::CreateSaveGameObject(UC_SaveGameData::StaticClass()));
	LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (!LoadGameInstance->IsValidLowLevel())
		LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::CreateSaveGameObject(UC_SaveGameData::StaticClass()));

	bool bContains = false;

	// Checks if Object already exists in save file
	for (int i = 0; i < LoadGameInstance->SaveBowls.Num(); ++i) {
		if (LoadGameInstance->SaveBowls[i].Name == Object->GetName()) {
			LoadGameInstance->SaveBowls[i].BowlExist = Object->bowlExist;
			LoadGameInstance->SaveBowls[i].Solved = Object->c_solved;
			LoadGameInstance->SaveBowls[i].Slot = Object->c_slot;
			bContains = true;
		}
	}// Saves Object into file if it doesnt exist
	if (!bContains && !Object->GetName().IsEmpty()) {
		FSaveBowlStruct SaveStruct;
		SaveStruct.Name = Object->GetName();
		SaveStruct.BowlExist = Object->bowlExist;
		SaveStruct.Solved = Object->c_solved;
		SaveStruct.Slot = Object->c_slot;
		LoadGameInstance->SaveBowls.Add(SaveStruct);

		bContains = true;
	}
	UGameplayStatics::SaveGameToSlot(LoadGameInstance, LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex);
}

void ASaveAndLoad::LoadBowl(AC_Bowl *Object) {
	UC_SaveGameData* LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::CreateSaveGameObject(UC_SaveGameData::StaticClass()));
	LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (!LoadGameInstance->IsValidLowLevel())
		return;

	for (int i = 0; i < LoadGameInstance->SaveBowls.Num(); ++i) {
		if (LoadGameInstance->SaveBowls[i].Name == Object->GetName()) {
			Object->bowlExist = LoadGameInstance->SaveBowls[i].BowlExist;
			Object->c_slot = LoadGameInstance->SaveBowls[i].Slot;
			Object->c_solved = LoadGameInstance->SaveBowls[i].Solved;
			Object->RefreshSlot();
		}
	}
}

// -------------------------------------------------------------
//						PLAYER CONTROLLER
// -------------------------------------------------------------

void ASaveAndLoad::SaveController() {
	UC_SaveGameData* LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::CreateSaveGameObject(UC_SaveGameData::StaticClass()));
	LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (!LoadGameInstance->IsValidLowLevel())
		return;

	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	AC_MainCharacter* tempCharacter = Cast<AC_MainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!tempCharacter->IsValidLowLevel())
		return;

	LoadGameInstance->SaveController.CanTimewalk = tempController->canTimewalk;
	LoadGameInstance->SaveController.CurrentTime = tempController->currentTime;
	LoadGameInstance->SaveController.Alpha = tempController->alpha;
	LoadGameInstance->SaveController.OldAlpha = tempController->oldAlpha;
	LoadGameInstance->SaveController.Dissolve = tempController->dissolve;
	LoadGameInstance->SaveController.SoundVolume = tempController->fSoundVolume;
	LoadGameInstance->SaveController.Position = tempCharacter->GetActorLocation();
	LoadGameInstance->SaveController.Rotation = tempCharacter->GetActorRotation();
	LoadGameInstance->SaveController.Sun = tempController->ambLight;
	LoadGameInstance->SaveController.Inventory = tempController->c_Inventory;

	UGameplayStatics::SaveGameToSlot(LoadGameInstance, LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex);
}

void ASaveAndLoad::LoadController() {
	UC_SaveGameData* LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::CreateSaveGameObject(UC_SaveGameData::StaticClass()));
	LoadGameInstance = Cast<UC_SaveGameData>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (!LoadGameInstance->IsValidLowLevel())
		return;
	
	AC_PlayerController* tempController = Cast<AC_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!tempController->IsValidLowLevel())
		return;

	AC_MainCharacter* tempCharacter = Cast<AC_MainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!tempCharacter->IsValidLowLevel())
		return;

	tempController->canTimewalk = LoadGameInstance->SaveController.CanTimewalk;
	tempController->currentTime = LoadGameInstance->SaveController.CurrentTime;
	tempController->alpha = LoadGameInstance->SaveController.Alpha;
	tempController->oldAlpha = LoadGameInstance->SaveController.OldAlpha;
	tempController->dissolve = LoadGameInstance->SaveController.Dissolve;
	tempController->fSoundVolume = LoadGameInstance->SaveController.SoundVolume;
	tempCharacter->SetActorLocation(LoadGameInstance->SaveController.Position);
	tempCharacter->SetActorRotation(LoadGameInstance->SaveController.Rotation);
	tempController->ambLight = LoadGameInstance->SaveController.Sun;
	tempController->c_Inventory = LoadGameInstance->SaveController.Inventory;
}