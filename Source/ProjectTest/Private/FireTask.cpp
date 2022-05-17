// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTask.h"



EBTNodeResult::Type UFireTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (!OwnerComp.GetAIOwner())
    {
        return EBTNodeResult::Failed;
    }
    ABasePlayer* ControlledPlayer = Cast<ABaseAIController>(OwnerComp.GetAIOwner())->GetPawn<ABasePlayer>();
    if (ControlledPlayer)
    {
        ControlledPlayer->Fire();
        return EBTNodeResult::Succeeded;
    }
	return EBTNodeResult::Failed;
}
