// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "BaseProjectile.generated.h"

UCLASS()
class PROJECTTEST_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Default component for projectile
	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditAnywhere)
		USphereComponent* SphereCollision;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float GetRadius();
	
};
