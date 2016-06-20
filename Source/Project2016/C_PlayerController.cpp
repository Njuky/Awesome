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


// Called every frame
void AC_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (WasInputKeyJustPressed(EKeys::G) || WasInputKeyJustPressed(EKeys::Gamepad_FaceButton_Top)) {
		if (c_Inventory->IsValidLowLevel()) {
			c_Inventory->c_DropItem();
		}
	}
}