// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EBlasterTurningInPlace : uint8
{
	EBTIP_Left UMETA(DisplayName = "Turning Left"),
	EBTIP_Right UMETA(DisplayName = "Turning Right"),
	EBTIP_NotTurning UMETA(DisplayName = "Not Turning"),

	EBTIP_MAX UMETA(DisplayName = "DefaultMAX")
};

class BLASTER_API BlasterTurningInPlace
{
public:
	BlasterTurningInPlace();
	~BlasterTurningInPlace();
};
