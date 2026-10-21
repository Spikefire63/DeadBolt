

#include "EnemyBaseController.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DeadBoltCharacter.h"

// Sets default values
AEnemyBaseController::AEnemyBaseController()
{
	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void AEnemyBaseController::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(ChaseTimer, this, &AEnemyBaseController::ChasePlayer, 0.5f, true);
		GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemyBaseController::TryAttack, 1.f, true);
	}
}

void AEnemyBaseController::ChasePlayer()
{
	AAIController* AI = Cast<AAIController>(GetController());
	APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);

	if (AI && Player)
	{
		AI->MoveToActor(Player, 100.f);
	}
}

void AEnemyBaseController::Hit(float Damage)
{
	Health -= Damage;

	if (Health <= 0.f)
	{
		Destroy();
	}
}

void AEnemyBaseController::TryAttack()
{
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (Player && FVector::Dist(GetActorLocation(), Player->GetActorLocation()) <= AttackRange)
	{
		UGameplayStatics::ApplyDamage(Player, AttackDamage, GetController(), this, UDamageType::StaticClass());
	}
}






