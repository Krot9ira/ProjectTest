// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckVisiblity.h"
#include <BasePlayer.h>
#include <BaseAIController.h>

UCheckVisiblity::UCheckVisiblity()
{
	NodeName = "IsDirectVisible";
}

EBTNodeResult::Type UCheckVisiblity::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//task check enemy visibility if player in direct visibility return succeed

	if (!OwnerComp.GetAIOwner())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	ABasePlayer* ControlledPlayer = Cast<ABaseAIController>(OwnerComp.GetAIOwner())->GetPawn<ABasePlayer>();
	ABasePlayer* EnemyPlayer = Cast<ABasePlayer>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject("Enemy"));
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(ControlledPlayer);
	FHitResult Hit;
	
	GetWorld()->LineTraceSingleByChannel(Hit, ControlledPlayer->GetActorLocation(), EnemyPlayer->GetActorLocation(), ECollisionChannel::ECC_Visibility, QueryParams, FCollisionResponseParams::DefaultResponseParam);

	if (Hit.Actor.Get() == EnemyPlayer)
	{
		//setting point to look with speed pre-emption
		OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector("Point", EnemyPlayer->GetActorLocation() + EnemyPlayer->GetVelocity()*0.1f);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
