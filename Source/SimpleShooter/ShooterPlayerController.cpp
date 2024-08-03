// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    HUDWidget = CreateWidget(this, HUDScreenClass);
    if(HUDWidget != nullptr)
    {
        HUDWidget->AddToViewport();
    }
}


void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    UUserWidget * ScreenWidgetToDisplay = nullptr;

    HUDWidget->RemoveFromParent();

    if(bIsWinner)
    {
        ScreenWidgetToDisplay = CreateWidget(this, WinScreenClass);
    }
    else
    {
        ScreenWidgetToDisplay = CreateWidget(this, LoseScreenClass);
    }
    
    if(ScreenWidgetToDisplay != nullptr)
    {
        ScreenWidgetToDisplay->AddToViewport();
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
}

