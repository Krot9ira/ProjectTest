// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomPointToGo.h"
#include <BasePlayer.h>
#include <ProjectTest/Public/BaseAIController.h>

EBTNodeResult::Type UFindRandomPointToGo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (!OwnerComp.GetAIOwner())
    {
        return EBTNodeResult::Failed;
    }
 
    ABasePlayer* ControlledPlayer = Cast<ABaseAIController>(OwnerComp.GetAIOwner())->GetPawn<ABasePlayer>();

	FNavLocation Location{};
    const UNavigationSystemV1* NavSystem{ UNavigationSystemV1::GetCurrent(GetWorld()) };
	NavSystem->GetRandomReachablePointInRadius(ControlledPlayer->GetActorLocation(),300.0f, Location);
	return EBTNodeResult::Succeeded;
}
