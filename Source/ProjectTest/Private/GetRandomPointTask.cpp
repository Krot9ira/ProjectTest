// Fill out your copyright notice in the Description page of Project Settings.


#include "GetRandomPointTask.h"

EBTNodeResult::Type UGetRandomPointTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (!OwnerComp.GetAIOwner())
    {
        return EBTNodeResult::Failed;
    }
    ABasePlayer* ControlledPlayer = Cast<ABaseAIController>(OwnerComp.GetAIOwner())->GetPawn<ABasePlayer>();
    //NavigationSystem::GetRandomReachablePointInRadius(ControlledPlayer->GetActorLocation();
	return EBTNodeResult::Failed;
}
