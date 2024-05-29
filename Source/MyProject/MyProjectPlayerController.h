// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyProjectPlayerController.generated.h"

class UInputMappingContext;

/**
 *
 */
UCLASS()
class MYPROJECT_API AMyProjectPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

	// End Actor interface
private:
	UFUNCTION(BlueprintCallable, Category = "Utility")
	static void SimulateLeftMouseButtonClick(bool bButtonDown)
	{
		FSlateApplication& SlateApp = FSlateApplication::Get();
		FPointerEvent MouseEvent(
			0, 
			SlateApp.CursorPointerIndex,
			SlateApp.GetCursorPos(),
			SlateApp.GetLastCursorPos(),
			SlateApp.GetPressedMouseButtons(),
			EKeys::LeftMouseButton, 
			0, 
			SlateApp.GetPlatformApplication()->GetModifierKeys()
		);

		if (bButtonDown)
		{
			SlateApp.ProcessMouseButtonDownEvent(nullptr, MouseEvent);
		}
		else
		{
			SlateApp.ProcessMouseButtonUpEvent(MouseEvent);
		}
	}	
};
