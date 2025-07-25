// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Projectile.h"
#include "ProjectileRocket.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AProjectileRocket : public AProjectile
{
	GENERATED_BODY()
public:
	AProjectileRocket();
	
protected:
	//UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector Normalimpulse, const FHitResult& Hit) override;

private:
	UPROPERTY(EditAnywhere, Category = "ProjectileRocket")
	float MinimumDamage = 10.f;

	UPROPERTY(EditAnywhere, Category = "ProjectileRocket")
	float InnerRadius = 200.f;

	UPROPERTY(EditAnywhere, Category = "ProjectileRocket")
	float OuterRadius = 500.f;
	
	UPROPERTY(EditAnywhere, Category = "ProjectileRocket")
	float DamageFalloff = 1.f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RocketMesh;
};
