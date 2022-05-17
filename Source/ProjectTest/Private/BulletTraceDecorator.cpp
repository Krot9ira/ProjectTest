// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTraceDecorator.h"
#include "Kismet/GameplayStatics.h"
#include <BasePlayer.h>
#include <ProjectTest/Public/BaseAIController.h>
#include "Math/UnrealMathUtility.h"

bool UBulletTraceDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    if (!OwnerComp.GetAIOwner())
    {
        return false;
    }
    //Checking possibility to hit enemy
    ABasePlayer* ControlledPlayer = Cast<ABaseAIController>(OwnerComp.GetAIOwner())->GetPawn<ABasePlayer>();
    if (ControlledPlayer)
    {
        FCollisionQueryParams Params;
        TArray<struct FHitResult> OutHits;
        FCollisionShape Shape = FCollisionShape();
        GetWorld()->SweepMultiByChannel(OutHits, ControlledPlayer->GetActorLocation(), ControlledPlayer->GetActorLocation(), FQuat(0,0,0,0), ECollisionChannel::ECC_Visibility, Shape.MakeSphere(500.0f), Params, FCollisionResponseParams::DefaultResponseParam);
    }

    

	return true;
}
