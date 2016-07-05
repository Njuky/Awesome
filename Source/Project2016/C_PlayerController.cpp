// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_PlayerController.h"

//Updates alpha per tick
bool AC_PlayerController::UpdateAlpha(float DeltaTime)
{
	bool returnBool = false;
	if (buttonPressed) {
		timeButtonPressed += DeltaTime;
		if (timeButtonPressed >= timewalkDelay && canTimewalk) {
			returnBool = true;
			if(!timeChanged)
				if (currentTime) {
					alpha = (timeButtonPressed - timewalkInitTime) / 2.5;
					alpha = 1 - FMath::Clamp(alpha, 0.0f, 1.0f);
				}else{
					alpha = (timeButtonPressed - timewalkInitTime) / 2.5;
					alpha = FMath::Clamp(alpha, 0.0f, 1.0f);
				}
		}
	}else{
		if (currentTime) {
			if (alpha != 1) {
				alpha += alphaRate;
				alpha = FMath::Clamp(alpha, 0.0f, 1.0f);
			}
		}else{
			if (alpha != 0) {
				alpha -= alphaRate;
				alpha = FMath::Clamp(alpha, 0.0f, 1.0f);
			}
		}
	}
	return returnBool;
}

void AC_PlayerController::cPlaySound(USoundBase* sound)
{
	if(sound->IsValidLowLevel())
		ClientPlaySound(sound, fSoundVolume, 1.0f);
}


// Called every frame
void AC_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (WasInputKeyJustPressed(EKeys::F) || WasInputKeyJustPressed(EKeys::Gamepad_FaceButton_Right)) {
		if (c_Inventory->IsValidLowLevel() && bCanInteract) {
			if (c_Inventory->c_sDrop->IsValidLowLevel() && !c_Inventory->bowl)
				ClientPlaySound(c_Inventory->c_sDrop, fSoundVolume, 1.0f);
			else if (c_sDrop->IsValidLowLevel() && !c_Inventory->bowl)
				ClientPlaySound(c_sDrop, fSoundVolume, 1.0f);

			c_Inventory->c_DropItem();
		}
		else if (c_TempInventory->IsValidLowLevel()) {
			if (c_TempInventory->c_sCollect->IsValidLowLevel())
				ClientPlaySound(c_TempInventory->c_sCollect, fSoundVolume, 1.0f);
			else if (c_sCollect->IsValidLowLevel())
				ClientPlaySound(c_sCollect, fSoundVolume, 1.0f);

			c_TempInventory->c_CollectItem();
		}
	}
}