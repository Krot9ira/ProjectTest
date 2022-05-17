// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NavigationSystem.h"
#include "FindRandomPointToGo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTEST_API UFindRandomPointToGo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFindRandomPointToGo();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
