#pragma once
#include "../PlayerStateBase.h"

class PlayerStateFactory
{
	//シングルトン用 ここから
private:
	static PlayerStateFactory* instance;

private:
	PlayerStateFactory() = default;
	PlayerStateFactory(const PlayerStateFactory&) = default;
	PlayerStateFactory& operator=(const PlayerStateFactory&) = default;
	//シングルトン用ここまで

private:
	class StoppedState* idle;
	class JumpingState* jump;
	class RunningState* run;
	class SquatState* squat;
	class DamageState* damage;

private:
	void Initialize(class Player& player);

public:
	static PlayerStateBase* Get(class Player& player, ePlayerState state);
	static void Finalize();
};

