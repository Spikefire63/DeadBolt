// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBaseController.generated.h"

UCLASS()
class DEADBOLT_API AEnemyBaseController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBaseController();

	void Hit(float Damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ChasePlayer();

	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	float Health = 100.f;

	FTimerHandle ChaseTimer;
};
