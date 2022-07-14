#include "pch.h"
#include "InputManager.h"
#include "Camera.h"
#include "DirectX.h"

InputManager::InputManager()
{
    InitializeInput();
}

bool InputManager::InitializeInput()
{
    RAWINPUTDEVICE Rid[1];  //Only adding keyboard here so we only need one device

    Rid[0].usUsagePage = 0x01;  //Generic device
    Rid[0].usUsage = 0x06; //Keyboard code
    Rid[0].dwFlags = 0; //How to interpret the device, this is the default value
    Rid[0].hwndTarget = 0; //Follows the keyboard focus

    //Register the provided device to get raw input data
    if (RegisterRawInputDevices(Rid, 1, sizeof(Rid[0])) == FALSE) {
        return false;
    }

    return true;
}

void InputManager::CheckInput(float deltaTime, Camera* cam, DirectX* directX)
{

    _speed = 0.1f;
    
    //Input
    if (::GetAsyncKeyState('Z') & 0x8000f)
    {
        cam->moveUpDown += _speed;
    }
    if (::GetAsyncKeyState('Q') & 0x8000f)
    {
        cam->GetTransform()->pitch -= _speed * 0.1f;
    }
    if (::GetAsyncKeyState('D') & 0x8000f)
    {
        cam->GetTransform()->pitch += _speed * 0.1f;
    }
    if (::GetAsyncKeyState('S') & 0x8000f)
    {
        cam->moveUpDown -= _speed;
    }
    if (::GetAsyncKeyState('A'))
    {
        cam->moveBackForward += _speed;
    }
    if (::GetAsyncKeyState('E') & 0x8000f)
    {
        cam->moveBackForward -= _speed;
    }
    if (::GetAsyncKeyState(VK_ESCAPE) & 0x8000f)
    {
        //PostQuitMessage(0); //Close game engine
        exit(0);
    }
}
