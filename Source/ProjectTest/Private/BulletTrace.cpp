// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletTrace.h"
#include "DrawDebugHelpers.h"




UBulletTrace::UBulletTrace()
{
    NodeName = "PredictBulletPath";
}

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
        Params.DrawDebugType = EDrawDebugTrace::None;
        Params.bTraceWithChannel = true;
        Params.bTraceWithCollision = true;
        Params.ActorsToIgnore.Add(ControlledPlayer);
        
        FPredictProjectilePathResult PathResult;

        ABasePlayer* EnemyPlayer = Cast<ABasePlayer>(OwnerComp.GetAIOwner()->GetBlackboardComponent()->GetValueAsObject("Enemy"));

        UObject* WorldContextObject = GetWorld();

        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(ControlledPlayer);

        TArray<struct FHitResult> OutHits;

        FCollisionShape Shape = FCollisionShape();

        GetWorld()->SweepMultiByChannel(OutHits, ControlledPlayer->GetActorLocation(), ControlledPlayer->GetActorLocation(), FQuat(0, 0, 0, 0), ECollisionChannel::ECC_Visibility, Shape.MakeSphere(5000.0f), QueryParams, FCollisionResponseParams::DefaultResponseParam);
        
        //points to check
        TArray<FVector> Points;
        for (int i = 90; i >= 0; i-=5)
        {
            Points.Add(FVector(FMath::Cos(i), FMath::Sin(i), 0));
        }
        
        /* Collect object to bouns and save point/ this implementation is not working
        //collecting ponts to check
        for (int a = 0; a < OutHits.Num(); a++)
        {
            if (!EnemyPlayer)
            {
                continue;
            }
            int32 BouncingPointX = OutHits[a].ImpactPoint.X;
            int32 PlayerLocationX = BouncingPointX - EnemyPlayer->GetActorLocation().X;
            int32 EnemyLocationX = BouncingPointX - ControlledPlayer->GetActorLocation().X;
            int32 PlayerWallLocation = OutHits[a].Actor.Get()->GetActorLocation().X - EnemyPlayer->GetActorLocation().X;
            int32 EnemyWallLocationX = OutHits[a].Actor.Get()->GetActorLocation().X - ControlledPlayer->GetActorLocation().X;
            if (PlayerWallLocation * EnemyWallLocationX < 0 || PlayerLocationX * EnemyLocationX < 0 || FMath::Abs(EnemyWallLocationX) < FMath::Abs(EnemyLocationX))
            {
                continue;
            }
            int BouncingPointY = ControlledPlayer->GetActorLocation().Y - (ControlledPlayer->GetActorLocation().Y - EnemyPlayer->GetActorLocation().Y) * FMath::Abs(EnemyLocationX) / FMath::Abs(EnemyLocationX + PlayerLocationX);
            if (OutHits[a].ImpactPoint.Y + 5000 < BouncingPointY || OutHits[a].ImpactPoint.Y - 5000 > BouncingPointY)
            {
                continue;
            }
            LaunchVector = FVector(BouncingPointX, BouncingPointY, 0);
            FHitResult ToEnemy;
            FHitResult ToSelf;
            QueryParams.AddIgnoredActor(OutHits[a].Actor.Get());
            GetWorld()->LineTraceSingleByChannel(ToEnemy, EnemyPlayer->GetActorLocation(), FVector(BouncingPointX, BouncingPointY, 71), ECollisionChannel::ECC_Visibility, QueryParams, FCollisionResponseParams::DefaultResponseParam);
            //DrawDebugLine(GetWorld(), EnemyPlayer->GetActorLocation(), FVector(bpx, bpy, 71), FColor::Red, false, 1);
            GetWorld()->LineTraceSingleByChannel(ToSelf, ControlledPlayer->GetActorLocation(), FVector(BouncingPointX, BouncingPointY, 72), ECollisionChannel::ECC_Visibility, QueryParams, FCollisionResponseParams::DefaultResponseParam);
            //DrawDebugLine(GetWorld(), ControlledPlayer->GetActorLocation(), FVector(bpx, bpy, 71), FColor::Green, false, 1);
            if (ToEnemy.Actor.Get() == EnemyPlayer && (ToSelf.Actor.Get() == ControlledPlayer || ToSelf.Actor.Get() == nullptr))
            {
                Points.Add(FVector(BouncingPointX, BouncingPointY, 0));
            }

        }
        */
        
        //Check points for bouncing hit
        for (int a = 0; a < Points.Num(); a++)
        {
            //Points[a].ToDirectionAndLength(Points[a], lenght);
            LaunchVector = Points[a];
            Params.StartLocation = ControlledPlayer->GetFireLocation();
            Params.ActorsToIgnore.Empty();
            Params.ActorsToIgnore.Add(ControlledPlayer);
            
            for (size_t i = 0; i < 3; i++)
            {
                float lenght = 0;
                FVector ToFire;
                
                
                bool bHit = UGameplayStatics::PredictProjectilePath(WorldContextObject, Params, PathResult);
                //DrawDebugLine(GetWorld(), Params.StartLocation, LaunchVector * 500, FColor::Green, false, 1);
                if (bHit)
                {   //If hit other player
                    if (i == 0)
                    {
                        ToFire = PathResult.HitResult.Location;
                    }
                    //DrawDebugLine(GetWorld(), Params.StartLocation, PathResult.HitResult.Location, FColor::Orange, false, 1);
                    if (Cast<ABasePlayer>(PathResult.HitResult.Actor))
                    {
                        OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector("Point", ToFire);
                        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
                        return EBTNodeResult::Succeeded;
                    }
                    //bouncing calculation
                    else
                    {
                        Params.StartLocation = PathResult.HitResult.ImpactPoint;
                        Params.ActorsToIgnore.Add(PathResult.HitResult.Actor.Get());
                        LaunchVector = FMath::GetReflectionVector(LaunchVector, PathResult.HitResult.Normal);
                        Params.LaunchVelocity = LaunchVector * 3000.0f;
                    }
                }
                //DrawDebugLine(GetWorld(), Params.StartLocation, Params.LaunchVelocity, FColor::Silver, false, 1);
            }
        }

       // FVector::CreateOrthonormalBasis()
        //i - count of bouncing wich we calculating, if hit other plyer we stop task
        Params.StartLocation = ControlledPlayer->GetFireLocation();
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
    FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
    return EBTNodeResult::Failed;
}
