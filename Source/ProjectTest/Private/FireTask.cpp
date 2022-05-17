// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTask.h"



EBTNodeResult::Type UFireTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (!OwnerComp.GetAIOwner())
    {
        return EBTNodeResult::Failed;
    }
    //If controlling player call fire
    ABasePlayer* ControlledPlayer = Cast<ABaseAIController>(OwnerComp.GetAIOwner())->GetPawn<ABasePlayer>();
    if (ControlledPlayer)
    {
        ControlledPlayer->Fire();

        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

        return EBTNodeResult::Succeeded;
    }
	return EBTNodeResult::Failed;
}
