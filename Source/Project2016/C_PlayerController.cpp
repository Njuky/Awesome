// Fill out your copyright notice in the Description page of Project Settings.

#include "Project2016.h"
#include "C_PlayerController.h"

//Updates alpha per tick
bool AC_PlayerController::UpdateAlpha(float DeltaTime, float runTime)
{
	bool returnBool = false;
	if (buttonPressed) {
		timeButtonPressed += DeltaTime;
		if (timeButtonPressed >= timewalkDelay && canTimewalk) {
			returnBool = true;
			if(!timeChanged)
				if (currentTime) {
					alpha = (timeButtonPressed - timewalkInitTime) / runTime;
					alpha = 1 - FMath::Clamp(alpha, 0.0f, 1.0f);
				}else{
					alpha = (timeButtonPressed - timewalkInitTime) / runTime;
					alpha = FMath::Clamp(alpha, 0.0f, 1.0f);
				}
		}
	}else{//Player released button early
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
	//Drop item
	if (WasInputKeyJustPressed(EKeys::Y))
		if (c_Inventory->IsValidLowLevel() && bCanInteract)
			c_Inventory->c_newDropItem();

	if (WasInputKeyJustPressed(EKeys::F) || WasInputKeyJustPressed(EKeys::Gamepad_FaceButton_Right)) {
		if (c_Inventory->IsValidLowLevel() && bCanInteract) {			
			animationType = 1;
		}//Collect item
		else if (c_TempInventory->IsValidLowLevel()) {
			animationType = c_TempInventory->animationType;
		}
	}
}