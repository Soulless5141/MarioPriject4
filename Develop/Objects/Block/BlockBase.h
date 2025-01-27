#pragma once
#include "../GameObject.h"
#include "../Character/Player/Player.h"

class BlockBase : public GameObject
{
public:
	class Player* player;

public:
	BlockBase();
	~BlockBase();

public:
	virtual void Initialize() override;
	virtual void Update(float) override;
	virtual void OnHitCollision(GameObject*) override;

};

