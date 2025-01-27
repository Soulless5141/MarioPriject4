#pragma once

#include "SceneBase.h"

// タイトルシーン
class TitleScene : public SceneBase
{
private:

	int back_ground_image;

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;
};

