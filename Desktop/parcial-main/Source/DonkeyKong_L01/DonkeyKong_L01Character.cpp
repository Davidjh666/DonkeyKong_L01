// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_L01Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Obstaculo.h"
#include "DonkeyKong_L01GameMode.h"

ADonkeyKong_L01Character::ADonkeyKong_L01Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 1500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	detener = false;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADonkeyKong_L01Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Parar", IE_Pressed, this, &ADonkeyKong_L01Character::Parar);
	//PlayerInputComponent->BindAction("Parar", IE_Released, this, &ADonkeyKong_L01Character::Parar);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADonkeyKong_L01Character::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADonkeyKong_L01Character::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADonkeyKong_L01Character::TouchStopped);
}

void ADonkeyKong_L01Character::Parar()
{
	//obstaculo01->setIncrementoZ(0.0f);
	detener = !detener;
	obstaculo01->setDetener(detener);
}

void ADonkeyKong_L01Character::BeginPlay()
{
	Super::BeginPlay();

	// Establecer la ubicación inicial del peón
	FVector InitialLocation = FVector(1220.0f, 4540.0f, 4700.0f); // Reemplaza estos valores con los que necesites
	SetActorLocation(InitialLocation);

	ADonkeyKong_L01GameMode* GameMode = Cast<ADonkeyKong_L01GameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		obstaculo01 = GameMode->obstaculo01;
	}
}

void ADonkeyKong_L01Character::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ADonkeyKong_L01Character::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ADonkeyKong_L01Character::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

