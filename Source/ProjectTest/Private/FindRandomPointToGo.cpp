// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomPointToGo.h"
#include <BasePlayer.h>
#include <ProjectTest/Public/BaseAIController.h>

UFindRandomPointToGo::UFindRandomPointToGo() 
{
    NodeName = (TEXT("Find random point"));
    BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UFindRandomPointToGo, BlackboardKey));
}

EBTNodeResult::Type UFindRandomPointToGo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (!OwnerComp.GetAIOwner())
    {
        return EBTNodeResult::Failed;
    }
 
    ABasePlayer* ControlledPlayer = Cast<ABaseAIController>(OwnerComp.GetAIOwner())->GetPawn<ABasePlayer>();

	FNavLocation Location{};

    const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	NavSystem->GetRandomReachablePointInRadius(ControlledPlayer->GetActorLocation(),300.0f, Location);

    OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location.Location);

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
