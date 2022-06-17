// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Components/LaserBeamComponent.h"
#include "HitableByLaser.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UHitableByLaser : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LASERPLUGIN_API IHitableByLaser
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "HitByLaser")
	void Hit(const FHitResult& HitInfo, const ULaserBeamComponent* Laser);
};
