// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <ProjectTest/Public/BaseProjectile.h>
#include "BasePlayer.generated.h"

UCLASS()
class ABasePlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	USceneComponent* FireLocation;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	TSubclassOf<ABaseProjectile> Bullet;

	UPROPERTY(BlueprintReadOnly)
		int32 Score;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* TreeAsset;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Main input functions
	UFUNCTION(BlueprintCallable)
		void MoveForward(float Axis);
	UFUNCTION(BlueprintCallable)
		void MoveRight(float Axis);
	UFUNCTION(BlueprintCallable)
		void Fire();

	//Functions for interacting with protected variables
	UFUNCTION(BlueprintCallable)
		int32 AddScore(int32 Points);

};
