// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"


// Sets default values
ABasePlayer::ABasePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!FireLocation) 
	{
		FireLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FireLocation"));
		FireLocation->SetupAttachment(RootComponent);
	}
	

	Score = 0;

}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);
	PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABasePlayer::Fire);

}

void ABasePlayer::MoveForward(float Axis)
{
	AddMovementInput(GetActorForwardVector(), Axis, false);
}

void ABasePlayer::MoveRight(float Axis)
{
	AddMovementInput(GetActorRightVector(), Axis, false);
}

void ABasePlayer::Fire()
{
	FActorSpawnParameters Params;
	Params.Instigator = this;
	FVector Location = FireLocation->GetComponentLocation();
	FRotator Rotation = FireLocation->GetComponentRotation();
	GetWorld()->SpawnActor(Bullet, &Location, &Rotation, Params);
}

int32 ABasePlayer::AddScore(int32 Points)
{
	++Score;
	return int32(Score);
}

