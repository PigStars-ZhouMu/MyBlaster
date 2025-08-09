#include "BlasterComponent/BuffComponent.h"
#include "Blaster/Public/Character/BlasterCharacter.h"
#include "Blaster/Public/Character/BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UBuffComponent::Heal(float HealAmount, float HealingTime)
{
	bHealing = true;
	HealingRate = HealAmount / HealingTime;
	AmountToHeal += HealAmount;
}

void UBuffComponent::RelenishShield(float ShieldAmount, float ReplenishTime)
{
	bReplenishingShield = true;
	ShieldRelenishRate = ShieldAmount / ReplenishTime;
	ShieldRelenishAmount += ShieldAmount;
}

void UBuffComponent::HealRampUp(float DeltaTime)
{
	if (!bHealing || Character == nullptr || Character->IsElimmed()) return;

	const float HealThisFrame = HealingRate * DeltaTime;
	Character->SetHealth(FMath::Clamp(Character->GetHealth() + HealThisFrame, 0.f, Character->GetMaxHealth()));
	Character->UpdateHUDHealth();
	AmountToHeal -= HealThisFrame;
	if (AmountToHeal <= 0.f || Character->GetHealth() >= Character->GetMaxHealth())
	{
		bHealing = false;
		AmountToHeal = 0.f;
	}
}

void UBuffComponent::ShieldRampUp(float DeltaTime)
{
	if (!bReplenishingShield || Character == nullptr || Character->IsElimmed()) return;

	const float ReplenishThisFrame = ShieldRelenishRate * DeltaTime;
	Character->SetShield(FMath::Clamp(Character->GetShield() + ReplenishThisFrame, 0.f, Character->GetMaxShield()));
	Character->UpdateHUDShield();
	ShieldRelenishAmount -= ReplenishThisFrame;
	if (ShieldRelenishAmount <= 0.f || Character->GetShield() >= Character->GetMaxShield())
	{
		bReplenishingShield = false;
		ShieldRelenishAmount = 0.f;
	}
}

void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBuffComponent::BuffSpeed(float BuffBaseSpeed, float BuffCrouchSpeed, float BuffTime)
{
	if (Character == nullptr) return;
	Character->GetWorldTimerManager().SetTimer(
		SpeedBuffTimer,
		this,
		&UBuffComponent::ResetSpeed,
		BuffTime
	);

	if (Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = BuffBaseSpeed;
		Character->GetCharacterMovement()->MaxWalkSpeedCrouched = BuffCrouchSpeed;
	}
	MulticastSpeedBuff(BuffBaseSpeed, BuffCrouchSpeed);
}

void UBuffComponent::ResetSpeed()
{
	if (Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = InitialBaseSpeed;
		Character->GetCharacterMovement()->MaxWalkSpeedCrouched = InitialCrouchSpeed;
		MulticastSpeedBuff(InitialBaseSpeed, InitialCrouchSpeed);
	}

}

void UBuffComponent::MulticastSpeedBuff_Implementation(float BaseSpeed, float CroutSpeed)
{
	if (Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
		Character->GetCharacterMovement()->MaxWalkSpeedCrouched = CroutSpeed;
	}
}

void UBuffComponent::BuffJump(float BuffJumpVelocity, float BuffTime)
{
	if (Character == nullptr) return;
	Character->GetWorldTimerManager().SetTimer(
		JumpBuffTimer,
		this,
		&UBuffComponent::ResetJump,
		BuffTime
	);
	if (Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->JumpZVelocity = BuffJumpVelocity;
	}
	MulticastJumpBuff(BuffJumpVelocity);
}

void UBuffComponent::MulticastJumpBuff_Implementation(float BuffJumpVelocity)
{
	if (Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->JumpZVelocity = BuffJumpVelocity;
	}
}

void UBuffComponent::ResetJump()
{
	if (Character && Character->GetCharacterMovement())
	{
		Character->GetCharacterMovement()->JumpZVelocity = InitialZVelocity;
	}
}

void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	HealRampUp(DeltaTime);
	ShieldRampUp(DeltaTime);
}

