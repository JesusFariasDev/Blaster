// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	// Setting up to blueprint the initial state for when weapon was not used before in the game 
	EWS_Initial UMETA(DisplayName = "Initial State"),
	EWS_Equipped UMETA(DisplayName = "Initial Equipped"),
	EWS_Dropped UMETA(DisplayName = "Initial Dropped"),

	// To show as numeric how many contants are in this enum
	EWS_MAX UMETA(DisplayName = "DefaultMAX")
};

UCLASS()
class BLASTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	
	// These parameters will be used in the delegate OnComponentBeginOverlap
	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

private:
	// Acessing mesh component
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	USkeletalMeshComponent* WeaponMesh;

	// Enable equipping this weapon when the character is close
	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	class USphereComponent* AreaSphere;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	EWeaponState WeaponState;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	class UWidgetComponent* PickupWidget;

public:	

};
