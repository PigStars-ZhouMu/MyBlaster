// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ProjectileRocket.h"
#include "Kismet/GameplayStatics.h"

AProjectileRocket::AProjectileRocket()
{
	RocketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketMesh"));
	RocketMesh->SetupAttachment(RootComponent);
	RocketMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
}

void AProjectileRocket::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector Normalimpulse, const FHitResult& Hit)
{
	APawn* FiringPawn = GetInstigator();
	if (FiringPawn)
	{
		AController* FiringController = FiringPawn->GetController();
		if (FiringController)
		{
			UGameplayStatics::ApplyRadialDamageWithFalloff(
				this, // world context object
				Damage, // Base damage
				MinimumDamage,
				GetActorLocation(), // origin
				InnerRadius,
				OuterRadius,
				DamageFalloff,
				UDamageType::StaticClass(), // DamageTypeClass
				TArray<AActor*>(), // Ingore Actors
				this,
				FiringController // Instigator controller
			);


		}
	}

	Super::OnHit(HitComp, OtherActor, OtherComp, Normalimpulse, Hit);
}
