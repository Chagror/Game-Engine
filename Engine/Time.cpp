#include "pch.h"
#include "Time.h"
#include "framework.h"

//int Time::fps = 0;

Time::Time()
{
    _targetFrameRate = 30.0f;
    _maxTimeStep = 1.0f / _targetFrameRate;
    _previousTime = timeGetTime();
    _elapsedTime = 0;
    _deltaTime = 0;

    _frames = 0;
    _fps = 0;
}

Time::~Time()
{

}

bool Time::Tick() {

    DWORD currentTime = timeGetTime();
    
    _deltaTime = (currentTime - _previousTime) / 1000.0f;

    if (_deltaTime <= 0.005f)
    {
        return false;
    }

    _previousTime = currentTime;

    // Cap the delta time to the max time step (useful if your 
    // debugging and you don't want the deltaTime value to explode.
    _deltaTime = std::min<float>(_deltaTime, _maxTimeStep);

    //calcul de FPS
    _frames += 1.0f;
    _elapsedTime += _deltaTime;
    if (_elapsedTime > 1.0f)
    {
        _fps = _frames / _elapsedTime;
        _frames = 0.0f;
        _elapsedTime = 0.0f;
    }
    //
    //DebugLog("FPS : " + std::to_string(fps));
    //DebugLog("DeltaTime : " + std::to_string(deltaTime));
    //DebugLog("ElapsedTime : " + std::to_string(elapsedTime));
    return true;
}
