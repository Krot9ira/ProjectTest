// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BulletTraceDecorator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTEST_API UBulletTraceDecorator : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
