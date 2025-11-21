// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/ProjectileRocket.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystemInstance.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Weapon/RocketMovementComponent.h"

AProjectileRocket::AProjectileRocket() {
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RocketMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RocketMovementComponent = CreateDefaultSubobject<URocketMovementComponent>(TEXT("RocketMovementComponent"));
	RocketMovementComponent->bRotationFollowsVelocity = true;
	RocketMovementComponent->SetIsReplicated(true);
	RocketMovementComponent->InitialSpeed = InitialSpeed;
	RocketMovementComponent->MaxSpeed = InitialSpeed;
}

void AProjectileRocket::BeginPlay() {
	Super::BeginPlay();
	if (!HasAuthority()) {
		CollisionBox->OnComponentHit.AddDynamic(this, &AProjectileRocket::OnHit);
	}
	SpawnTrailSystem();
	if (ProjectileLoop && LoopingSoundAttenuation) {
		ProjectileLoopComponent = UGameplayStatics::SpawnSoundAttached(
			ProjectileLoop,
			GetRootComponent(),
			FName(),
			GetActorLocation(),
			EAttachLocation::KeepWorldPosition,
			false,
			1.f,
			1.f,
			0.f,
			LoopingSoundAttenuation,
			(USoundConcurrency*)nullptr,
			false
		);
	}
}

void AProjectileRocket::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector Normalimpulse, const FHitResult& Hit) {
	if (OtherActor == GetOwner()) {
		return;
	}
	ExplodeDamage();
	StartDestoryTimer();

	if (ImpactParticle) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, GetActorTransform());
	}
	if (ImpactSound) {
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	}
	if (ProjectileMesh) {
		ProjectileMesh->SetVisibility(false);
	}
	if (CollisionBox) {
		CollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if (TrailSystemComponent && TrailSystemComponent->GetSystemInstance()) {
		TrailSystemComponent->GetSystemInstance()->Deactivate();
	}
	if (ProjectileLoopComponent && ProjectileLoopComponent->IsPlaying()) {
		ProjectileLoopComponent->Stop();
	}
}

void AProjectileRocket::Destroyed() {
}

#if WITH_EDITOR
void AProjectileRocket::PostEditChangeProperty(FPropertyChangedEvent& Event) {
	Super::PostEditChangeProperty(Event);
	FName PropertyName = Event.Property != nullptr ? FName(Event.Property->GetName()) : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(AProjectileRocket, InitialSpeed)) {
		if (ProjectileMovementComponent) {
			ProjectileMovementComponent->InitialSpeed = InitialSpeed;
			ProjectileMovementComponent->MaxSpeed = InitialSpeed;
		}
	}
}
#endif
