// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include <BasePlayer.h>
#include <ProjectTest/Public/BaseAIController.h>
#include "FireTask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTEST_API UFireTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
