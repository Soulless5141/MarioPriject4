#pragma once

#include "SceneBase.h"

class ResultScene : public SceneBase
{
private:
	int back_ground_stage;
	float time_limit;
	int now_life;
	int score;

public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;
};

