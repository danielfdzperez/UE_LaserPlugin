// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	static int32 DebugBeam;

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
	void TurnOff();

	/**
	* @BRIEF Turn on the laser without animations.
	*/
	UFUNCTION(BlueprintCallable)
	void TurnOn();

	/**
	* @BRIEF Called when starts off and turn on with sounds and animations.
	*
	* @see TurnOn
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Shoot();
	virtual void Shoot_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void Draw(const FHitResult& HitInfo, const FVector& Source, const FVector& Destination);
	virtual void Draw_Implementation(const FHitResult& HitInfo, const FVector& Source, const FVector& Destination) {};


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DebugBeamAction(const FVector& source, const FVector& destination, FColor color = FColor::Red);
	virtual void DebugBeamAction_Implementation(const FVector& source, const FVector& destination, FColor color = FColor::Red);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
#pragma endregion Methods
	
};
