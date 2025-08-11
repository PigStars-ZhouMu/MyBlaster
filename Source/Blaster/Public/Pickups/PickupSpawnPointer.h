// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupSpawnPointer.generated.h"

UCLASS()
class BLASTER_API APickupSpawnPointer : public AActor
{
	GENERATED_BODY()
	
public:	
	APickupSpawnPointer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class APickup>> PickupClasses;

	UPROPERTY()
	APickup* SpawnedPickup;

	void SpawnPickup();
	void SpawnPickupTimerFinished();
	UFUNCTION()
	void StartPickupTimer(AActor* DestoryedActor);

private:
	FTimerHandle SpawnPickupTimer;

	UPROPERTY(EditAnywhere)
	float SpawnPickupTimeMin;

	UPROPERTY(EditAnywhere)
	float SpawnPickupTimeMax;

public:	
	virtual void Tick(float DeltaTime) override;

	
	
};
