#pragma once
#include "Vector2D.h"
#include "Singleton.h"

#define D_WIN_MAX_X		(640)	// �X�N���[���T�C�Y�i���j
#define D_WIN_MAX_Y		(480)	// �X�N���[���T�C�Y�i�����j
#define STAGE_SIZE_X	(6720)
#define STAGE_SIZE_Y	(480)
#define OBJECT_SIZE (32)
#define D_COLOR_BIT		(32)	// �J���[�r�b�g

class Camera :public Singleton<Camera>
{
private:
	Vector2D camera_location;			//
	Vector2D screen_location_origin;	//
	Vector2D screen_location;

public:
	void CameraUpdate(Vector2D location);
	Vector2D ConvertLcoationToScreen(Vector2D location);
	Vector2D GetCameraLocation();

};

