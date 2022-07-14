#pragma once

class DirectX;
class Camera;
class InputManager
{
private:
	float _speed;

public:
	InputManager();
	bool InitializeInput();

	void CheckInput(float deltaTime, Camera* cam, DirectX* directX);
};

