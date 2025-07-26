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

	virtual void Destroyed() override;
	
protected:
	//UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector Normalimpulse, const FHitResult& Hit) override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* TrailSystem;

	void DestoryTimerFinished();

	UPROPERTY()
	class UNiagaraComponent* TrailSystemComponent;

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

	FTimerHandle DestoryTimer;

	UPROPERTY(EditAnywhere)
	float DestoryTime = 3.f;
};
