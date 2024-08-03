// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Gun.h"


// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	
}

void AGun::PullTrigger()
{

	if(MuzzleFlash && MuzzleSound){
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	}

	FHitResult BulletHitresult;
	FVector ShotDirection;

	if(GunTrace(BulletHitresult, ShotDirection))
	{
		AActor * HitActor = BulletHitresult.GetActor();
		if(HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, BulletHitresult, ShotDirection, nullptr);
			AController * OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
		if(HitFlash && HitSound)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, BulletHitresult.ImpactPoint, ShotDirection.Rotation());
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, BulletHitresult.ImpactPoint, ShotDirection.Rotation());
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& BulletHitresult, FVector& ShotDirection)
{
	
	FVector CameraLocation;
	FRotator CameraRotation;

	AController * OwnerController = GetOwnerController();
	if(OwnerController == nullptr){
		return false;
	}
	
	OwnerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector EndLine = CameraLocation + CameraRotation.Vector() * MaxRange;

	ShotDirection = -CameraRotation.Vector();

	FCollisionQueryParams Param;
	Param.AddIgnoredActor(this);
	Param.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(BulletHitresult, CameraLocation , EndLine, ECollisionChannel::ECC_GameTraceChannel1, Param);
}

AController* AGun::GetOwnerController() const
{
	APawn * OwnerPawn = Cast<APawn>(GetOwner());
	if(OwnerPawn == nullptr) return nullptr;
	
	return OwnerPawn->GetController();
}

