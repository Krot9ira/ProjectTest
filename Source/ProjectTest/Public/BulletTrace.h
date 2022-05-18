// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Kismet/GameplayStatics.h"
#include <BasePlayer.h>
#include <ProjectTest/Public/BaseAIController.h>
#include "Math/UnrealMathUtility.h"
#include "BulletTrace.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTEST_API UBulletTrace : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBulletTrace();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
