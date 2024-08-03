// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "BTT_Shoot.h"


UBTT_Shoot::UBTT_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTT_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController * AIOwner = OwnerComp.GetAIOwner();

    if(AIOwner == nullptr){
        return EBTNodeResult::Failed;
    }

    AShooterCharacter* AIPawn = Cast<AShooterCharacter>(AIOwner->GetPawn());

    if(AIPawn  == nullptr){
        return EBTNodeResult::Failed;
    }
    
    AIPawn->Shoot();

    return EBTNodeResult::Succeeded;
}
