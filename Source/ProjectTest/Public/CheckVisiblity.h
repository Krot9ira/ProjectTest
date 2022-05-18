// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "CheckVisiblity.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTEST_API UCheckVisiblity : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UCheckVisiblity();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
