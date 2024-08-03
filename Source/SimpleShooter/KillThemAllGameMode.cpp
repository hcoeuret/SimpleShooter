// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "AIController.h"
#include "ShooterAIController.h"
#include "KillThemAllGameMode.h"



void AKillThemAllGameMode::PawnKilled(APawn * PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController * PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    AShooterAIController * AIController = Cast<AShooterAIController>(PawnKilled->GetController());
    
    if (AIController != nullptr)
    {
         for (AShooterAIController * Controller : TActorRange<AShooterAIController>(GetWorld()))
        {
            if(Controller->IsDead() == false)
            {
                return;
            }
        }
        EndGame(true);
    }
   
}

void AKillThemAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController * Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsControllerPlayer = Controller->IsPlayerController();
        if(bIsPlayerWinner)
        {  
            Controller->GameHasEnded(Controller->GetPawn(),bIsControllerPlayer);
        }
        else
        {
            Controller->GameHasEnded(Controller->GetPawn(),!bIsControllerPlayer); 
        }
    }
}
