// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTService_UpdateLocationIfSeen.h"


UBTService_UpdateLocationIfSeen::UBTService_UpdateLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_UpdateLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn * PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(PlayerPawn == nullptr){
        return;
    }

    AAIController * AIOwner = OwnerComp.GetAIOwner();
    
    if(AIOwner == nullptr){
        return;
    }

     if(AIOwner->LineOfSightTo(PlayerPawn))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }

}
