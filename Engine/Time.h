#pragma once

class Time
{
	DWORD _previousTime;

	float _targetFrameRate;
	float _maxTimeStep;
	float _elapsedTime;
	float _deltaTime;

	int _frames;
	int _fps;

public:
	Time();
	~Time();

	//int static fps;
	int GetFps() const { return _fps; }
	float GetDeltaTime() const { return _deltaTime; }

	bool Tick();
};

