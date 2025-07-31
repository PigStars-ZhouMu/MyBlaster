// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Projectile.h"
#include "ProjectileGrenade.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AProjectileGrenade : public AProjectile
{
	GENERATED_BODY()
public:
	AProjectileGrenade();
protected:
	void BeginPlay();

	void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
	
	
};
