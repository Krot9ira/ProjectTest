// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"


ABaseAIController::ABaseAIController(const FObjectInitializer& Objectinitializer)
{
	BBC = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Cpmponent"));
	BTC = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ABasePlayer* Chr = Cast<ABasePlayer>(InPawn);
	if (Chr != nullptr && Chr->TreeAsset != nullptr)
	{
		//Initialize the BB
		BBC->InitializeBlackboard(*Chr->TreeAsset->BlackboardAsset);

		//Set BB 
		Enemy = BBC->GetKeyID("TargetActor");

		// Start the BT
		BTC->StartTree(*Chr->TreeAsset);
	}
}

