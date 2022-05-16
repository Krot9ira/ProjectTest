// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasePlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTEST_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(transient)
		class UBehaviorTreeComponent* BTC;
	UPROPERTY(transient)
		class UBlackboardComponent* BBC;

	//BB key 
	uint8 Enemy;

	
};
