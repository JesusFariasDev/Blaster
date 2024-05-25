// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadWidget.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API UOverheadWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// Controlling the text in the property 
	UPROPERTY(meta = (BindWidget))
	// Mapped in the hierarchy of the blueprint in Unreal project with the same name
	class UTextBlock* DisplayText;

	void SetDisplayText(FString TextToDisplay);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(APawn* InPawn);

protected:
	// When player disconnect or travel to other level, remove from the previous level
	virtual void NativeDestruct() override;
	// Use OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) under UE version 5

};
