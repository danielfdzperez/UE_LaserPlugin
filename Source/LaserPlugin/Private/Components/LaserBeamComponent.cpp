// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LaserBeamComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interfaces/HitableByLaser.h"

int32 ULaserBeamComponent::DebugBeam = 0;
FAutoConsoleVariableRef ConVarDebugFocusTracer(TEXT("LaserBeam.DebugBeam"), ULaserBeamComponent::DebugBeam, TEXT("Draw debug line"), ECVF_Cheat);

void ULaserBeamComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FHitResult Hit;
	FVector beamDestination = GetForwardVector() * MaxRayTraceDistance + GetComponentLocation();
	FCollisionQueryParams TraceParams;
	//bool isHit = ActorLineTraceSingle(Hit, GetActorLocation(), dest, CollisionChannel, TraceParams);
	bool isHit = GetWorld()->LineTraceSingleByChannel(Hit, GetComponentLocation(), beamDestination, CollisionChannel);

	if (isHit)
	{	
		if (Hit.GetActor()->GetClass()->ImplementsInterface(UHitableByLaser::StaticClass()))
		{
			IHitableByLaser::Execute_Hit(Hit.GetActor(), Hit, this);
		}
		ImpactReaction(Hit);
	}

#if WITH_EDITOR
	if (DebugBeam == 1)
	{
		if (isHit)
		{
			beamDestination = Hit.ImpactPoint;
		}
		DebugBeamAction(GetComponentLocation(), beamDestination);
	}
#endif

}

void ULaserBeamComponent::DebugBeamAction_Implementation(const FVector& source, const FVector& destination, FColor color)
{
	DrawDebugLine(GetWorld(), source, destination, color, false, 0);
}

// Called when the game starts or when spawned
void ULaserBeamComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.Target = this;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(true);
	PrimaryComponentTick.RegisterTickFunction(GetComponentLevel());
	if (BeginActive)
		TurnOn();
	else
		TurnOff();
	UE_LOG(LogTemp, Error, TEXT("BeginPlay"));
}

// Called every frame
//void ALaserBeam::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//	FHitResult Hit;
//	FVector dest = GetActorForwardVector() * MaxRayTraceDistance + GetActorLocation();
//	FCollisionQueryParams TraceParams;
//	//bool isHit = ActorLineTraceSingle(Hit, GetActorLocation(), dest, CollisionChannel, TraceParams);
//	bool isHit = GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), dest, CollisionChannel);
//
//	DrawDebugLine(GetWorld(), GetActorLocation(), dest, FColor::Red, false, 2);
//
//	if (isHit)
//	{
//		IHitableByLaser* Interface = dynamic_cast<IHitableByLaser*>(Hit.GetActor());
//		UHitableByLaser* Interface2 = dynamic_cast<UHitableByLaser*>(Hit.GetActor());
//		if(Interface != nullptr)
//		{
//			Interface->Hit();
//		}
//		ImpactReaction(GetActorLocation(), Hit.ImpactPoint);
//	}
//}

ULaserBeamComponent::ULaserBeamComponent()
{
	//PrimaryComponentTick.bCanEverTick = false;
	//PrimaryComponentTick.bStartWithTickEnabled = true;
#if WITH_EDITOR
		bTickInEditor = true;
		PrimaryComponentTick.bCanEverTick = true;
		PrimaryComponentTick.bStartWithTickEnabled = true;
#endif
}

void ULaserBeamComponent::TurnOff()
{
	CurrentlyActive = false;
}

void ULaserBeamComponent::TurnOn()
{
	CurrentlyActive = true;
}

void ULaserBeamComponent::Shoot()
{
	//Play audio or something
	TurnOn();
}
