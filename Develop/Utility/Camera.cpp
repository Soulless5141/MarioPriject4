#include "Camera.h"
#include "DxLib.h"

void Camera::CameraUpdate(Vector2D location)
{
	if (location.x + OBJECT_SIZE / 2 > camera_location.x)
	{
		camera_location = location + OBJECT_SIZE / 2;
	}

	if (camera_location.x - (D_WIN_MAX_X / 2.0f) <= 0.0f)
	{
		camera_location.x = (D_WIN_MAX_X / 2.0f);
	}
	else if (camera_location.x + (D_WIN_MAX_X / 2.0f) >= STAGE_SIZE_X)
	{
		camera_location.x = STAGE_SIZE_X - (D_WIN_MAX_X / 2.0f);
	}

	if (camera_location.y - (D_WIN_MAX_Y / 2.0f) <= 0.0f)
	{
		camera_location.y = (D_WIN_MAX_Y / 2.0f);
	}
	else if (camera_location.y + (D_WIN_MAX_Y / 2.0f) >= STAGE_SIZE_Y)
	{
		camera_location.y = STAGE_SIZE_Y - (D_WIN_MAX_Y / 2.0f);
	}
}

Vector2D Camera::ConvertLcoationToScreen(Vector2D location)
{
	screen_location_origin = {
		camera_location.x - D_WIN_MAX_X / 2.0f,
		camera_location.y - D_WIN_MAX_Y / 2.0f
	};


	screen_location = {
		location.x - screen_location_origin.x,
		location.y - screen_location_origin.y
	};
	return screen_location;
}

Vector2D Camera::GetCameraLocation()
{
	return camera_location;
}