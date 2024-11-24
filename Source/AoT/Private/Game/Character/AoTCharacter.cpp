// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Character/AoTCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/AoTAbilitySystemComponent.h"
#include "Game/PlayerState/AoTPlayerState.h"
#include "Data/Character/CharacterClassInfo.h"
#include "Game/GameMode/AoTGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystem/AoTAbilitySystemComponent.h"

AAoTCharacter::AAoTCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

UAbilitySystemComponent* AAoTCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAoTCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
}

void AAoTCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAoTCharacter::InitAbilityActorInfo()
{
	if (AAoTPlayerState* AoTPlayerState = GetPlayerState<AAoTPlayerState>())
	{
		AbilitySystemComponent = AoTPlayerState->GetAoTAbilitySystemComponent();
		if (IsValid(AbilitySystemComponent))
		{
			AbilitySystemComponent->InitAbilityActorInfo(AoTPlayerState, this);
			InitClassDefaults();

		}
	}
}

void AAoTCharacter::InitClassDefaults()
{
	if (AAoTGameMode* GasGameMode = Cast<AAoTGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		if (UCharacterClassInfo* ClassInfo = GasGameMode->GetCharacterClassInfo())
		{
			if (FCharacterClassDefaultInfo* CharacterClassInfo = ClassInfo->ClassDefaultsInfo.Find(CharacterTag))
			{
				AbilitySystemComponent->AddCharacterAbilities(CharacterClassInfo->DefaultAbilities);
				AbilitySystemComponent->InitDefaultAttributes(CharacterClassInfo->DefaultAttributes);
			}
		}
	}
}

void AAoTCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAoTCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

