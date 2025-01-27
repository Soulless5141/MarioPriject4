#pragma once


#include "../Utility/Singleton.h"
#include "SceneBase.h"

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneBase* current_scene;	// ���݂̃V�[�����

public:
	SceneManager();
	~SceneManager();

public:
	void Initialize();
	bool Update(float delta_second);
	void Finalize();


	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	/// <param name="next_type">���̃V�[���^�C�v</param>
	void ChangeScene(eSceneType next_type);

private:
	/// <summary>
	/// �V�[����������
	/// </summary>
	/// <param name="next_type">���̃V�[���^�C�v</param>
	/// <returns>���������V�[�����̃|�C���^</returns>
	SceneBase* CreateScene(eSceneType next_type);

	/// <summary>
/// �`�揈��
/// </summary>
	void Graph() const;
};