// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTrace.h"




EBTNodeResult::Type UBulletTrace::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (!OwnerComp.GetAIOwner())
    {
        return EBTNodeResult::Failed;
    }
    //Checking possibility to hit enemy
    ABasePlayer* ControlledPlayer = Cast<ABaseAIController>(OwnerComp.GetAIOwner())->GetPawn<ABasePlayer>();
    if (ControlledPlayer)
    {
        FVector LaunchVector = ControlledPlayer->GetActorForwardVector();
        //Parameters of projectile sets there
        FPredictProjectilePathParams Params;
        Params.StartLocation = ControlledPlayer->GetFireLocation();
        Params.ProjectileRadius = 5.5f;
        Params.LaunchVelocity = LaunchVector* 3000.0f;
        Params.OverrideGravityZ = 0.01f;
        Params.TraceChannel = ECollisionChannel::ECC_Visibility;
        Params.DrawDebugType = EDrawDebugTrace::ForOneFrame;
        Params.bTraceWithChannel = true;
        Params.bTraceWithCollision = true;
        Params.ActorsToIgnore.Add(ControlledPlayer);

        FPredictProjectilePathResult PathResult;

        UObject* WorldContextObject = GetWorld();

        //i - count of bouncing wich we calculating, if hit other plyer we stop task
        for (size_t i = 0; i < 3; i++)
        {
            bool bHit = UGameplayStatics::PredictProjectilePath(WorldContextObject, Params, PathResult);
            if (bHit)
            {   //If hit other player
                if (Cast<ABasePlayer>(PathResult.HitResult.Actor))
                {
                    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                    return EBTNodeResult::Succeeded;
                }
                //bouncing calculation
                else
                {
                    Params.StartLocation = PathResult.HitResult.Location;
                    Params.ActorsToIgnore.Add(PathResult.HitResult.Actor.Get());
                    LaunchVector = FMath::GetReflectionVector(LaunchVector, PathResult.HitResult.Normal);
                    Params.LaunchVelocity = LaunchVector * 3000.0f;
                }
            }
        }
        

        
    }
    
    return EBTNodeResult::Failed;
}
