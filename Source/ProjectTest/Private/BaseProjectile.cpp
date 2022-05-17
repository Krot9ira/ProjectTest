// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	if (!ProjectileMovementComponent)
	{
		ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	}
	if (!SphereCollision)
	{
		SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		RootComponent = SphereCollision;
	}
	

}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABaseProjectile::GetRadius()
{
	//if (!SphereCollision)
	//{
	return 0.0f;
	//}
	//return SphereCollision->GetScaledSphereRadius();
}



