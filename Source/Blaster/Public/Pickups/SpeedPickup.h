// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/Pickup.h"
#include "SpeedPickup.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API ASpeedPickup : public APickup
{
	GENERATED_BODY()
//public:
//	ASpeedPickup();
	
protected:
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepReult
	);
	
private:
	UPROPERTY(EditAnywhere)
	float BaseSpeedBuff = 1600.f;

	UPROPERTY(EditAnywhere)
	float CrouchSpeedBuff = 850.f;

	UPROPERTY(EditAnywhere)
	float SpeedBuffTime = 30.f;

	
};
