// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Blaster/Character/BlasterCharacter.h"

AWeapon::AWeapon()
{
	// Set to false
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	// Instantiating Unreal component and setting up
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	// Setting up the root connection
	SetRootComponent(WeaponMesh);

	// Setting up collision in the weapon top bounce off
	WeaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	// Making the pawn ignore and step over it
	WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	// Disable collision (will collide just in specific moments dropping or throwing)
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Will detect when overlapping the object to character take the weapon or not
	AreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	AreaSphere->SetupAttachment(RootComponent);

	// Setting sphere disapear (we will need set up to work just in server side on BeginPlay function)
	AreaSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// Setting sphere to disable collisions
	AreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);
}

void AWeapon::BeginPlay()

{
	Super::BeginPlay();
	
	if (HasAuthority()) 
	{
		AreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		AreaSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		// This line is calling OnComponentBeginOverlap delegate and AddDynamics is using the OnSphereOverlap content as the parameters
		AreaSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnSphereOverlap);
	}
	if (PickupWidget)
	{
		PickupWidget->SetVisibility(false);
	}
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Overlapping the sphere will cast widget to ABlasterCharacter type (otherActor represents the weapon widget)
	ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor);
	if (PickupWidget)
	{
		PickupWidget->SetVisibility(true);
	}
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

