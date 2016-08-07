// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "MGameMode.h"

void AMGameMode::SetSoundClassVolume(USoundClass* TargetSoundClass, float NewVolume) {
	if (TargetSoundClass) {
		TargetSoundClass->Properties.Volume = NewVolume;

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.Owner = this;

		ASaveAndLoad* temp = GetWorld()->SpawnActor<ASaveAndLoad>(ASaveAndLoad::StaticClass(), FVector(0,0,0), FRotator(0,0,0), SpawnInfo);
		temp->SaveSettings();
		temp->Destroy();
	}
}