// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTraceDecorator.h"
#include "Kismet/GameplayStatics.h"
#include <BasePlayer.h>
#include <ProjectTest/Public/BaseAIController.h>
#include "Math/UnrealMathUtility.h"

UBulletTraceDecorator::UBulletTraceDecorator()
{
	NodeName = "IsVisible";
}

bool UBulletTraceDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//If enemy in direct visibility return false
    if (!OwnerComp.GetAIOwner())
    {
        return false;
    }
	ABasePlayer* ControlledPlayer = Cast<ABaseAIController>(OwnerComp.GetAIOwner())->GetPawn<ABasePlayer>();
	ABasePlayer* EnemyPlayer = Cast<ABasePlayer>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject("Enemy"));
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(ControlledPlayer);
	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(Hit, ControlledPlayer->GetActorLocation(), EnemyPlayer->GetActorLocation(), ECollisionChannel::ECC_Visibility, QueryParams, FCollisionResponseParams::DefaultResponseParam);

	if (Hit.Actor.Get() == EnemyPlayer)
	{
		
		return false;
	}

    

	return true;
}
