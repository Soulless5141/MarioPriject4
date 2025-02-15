#include "PlayerStateFactory.h"

#include "../StoppedState.h"
#include "../JumpingState.h"
#include "../RunningState.h"
#include "../SquatState.h"
#include "../DamageState.h"

#include "../../Player.h"

PlayerStateFactory* PlayerStateFactory::instance = nullptr;

// 各ステータスの生成
void PlayerStateFactory::Initialize(class Player& player)
{
	idle = new StoppedState(&player);
	jump = new JumpingState(&player);
	run = new RunningState(&player);
	squat = new SquatState(&player);
	damage = new DamageState(&player);
}

void PlayerStateFactory::Finalize()
{
	instance->idle->Finalize();
	instance->jump->Finalize();
	instance->run->Finalize();
	instance->squat->Finalize();
	instance->damage->Finalize();

	delete instance->idle;
	delete instance->jump;
	delete instance->run;
	delete instance->squat;
	delete instance->damage;
}

PlayerStateBase* PlayerStateFactory::Get(Player& player, ePlayerState state)
{
	if (instance == nullptr)
	{
		instance = new PlayerStateFactory();
		instance->Initialize(player);
	}

	PlayerStateBase* ret = nullptr;
	switch (state)
	{
	case ePlayerState::eIdle:
		instance->idle->Initialize();
		ret = instance->idle;
		break;
	case ePlayerState::eJump:
		instance->jump->Initialize();
		ret = instance->jump;
		break;
	case ePlayerState::eRun:
		instance->run->Initialize();
		ret = instance->run;
		break;
	case ePlayerState::eSquat:
		instance->squat->Initialize();
		ret = instance->squat;
		break;
	case ePlayerState::eDamage:
		instance->damage->Initialize();
		ret = instance->damage;
	default:
		break;
	}

	return ret;
}