// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "LaserBeamComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = ("Laser Plugin"), meta = (BlueprintSpawnableComponent), Blueprintable)
class LASERPLUGIN_API ULaserBeamComponent : public USceneComponent

{
	GENERATED_BODY()

#pragma region Attributes	
public:
	UPROPERTY(EditAnywhere)
		bool BeginActive = true;

	UPROPERTY(EditAnywhere)
		float MaxRayTraceDistance = 999999;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<ECollisionChannel> CollisionChannel = ECollisionChannel::ECC_Visibility;

protected:
	bool CurrentlyActive;
#pragma endregion Attributes

#pragma region Methods	
public:

	ULaserBeamComponent();

	// Called every frame
	//virtual void Tick(float DeltaTime) override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	* @BRIEF Turn off the laser without animations.
	*/
	UFUNCTION(BlueprintCallable)
		virtual void TurnOff();

	/**
	* @BRIEF Turn on the laser without animations.
	*/
	UFUNCTION(BlueprintCallable)
		virtual void TurnOn();

	/**
	* @BRIEF Called when starts off and turn on with sounds and animations.
	*
	* @see TurnOn
	*/
	UFUNCTION(BlueprintCallable)
		virtual void Shoot();

	UFUNCTION(BlueprintImplementableEvent)
	void ImpactReaction(const FVector& Origin, const FVector& End);
	virtual void ImpactReaction_Implementation(FVector const& Origin, FVector const& End) {};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
#pragma endregion Methods
	
};
