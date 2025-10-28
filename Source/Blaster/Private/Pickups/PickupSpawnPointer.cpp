
#include "Pickups/PickupSpawnPointer.h"
#include "Pickups/Pickup.h"


APickupSpawnPointer::APickupSpawnPointer() {
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void APickupSpawnPointer::BeginPlay() {
	Super::BeginPlay();
	StartPickupTimer((AActor*)nullptr);
}

void APickupSpawnPointer::SpawnPickup() {
	int32 NumPickupClasses = PickupClasses.Num();
	if (NumPickupClasses > 0) {
		int32 Selection = FMath::RandRange(0, NumPickupClasses - 1);
		SpawnedPickup = GetWorld()->SpawnActor<APickup>(
			PickupClasses[Selection],
			GetActorTransform()
		);
		if (HasAuthority() && SpawnedPickup) {
			SpawnedPickup->OnDestroyed.AddDynamic(this, &APickupSpawnPointer::StartPickupTimer);
		}

	}
}

void APickupSpawnPointer::SpawnPickupTimerFinished() {
	if (HasAuthority()) {
		SpawnPickup();
	}
}

void APickupSpawnPointer::StartPickupTimer(AActor* DestoryedActor) {
	const float SpawnTime = FMath::FRandRange(SpawnPickupTimeMin, SpawnPickupTimeMax);
	GetWorldTimerManager().SetTimer(
		SpawnPickupTimer,
		this,
		&APickupSpawnPointer::SpawnPickupTimerFinished,
		SpawnTime
	);
}

void APickupSpawnPointer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

