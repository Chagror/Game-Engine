#pragma once

#pragma comment(lib, "d3d9.lib")
#ifdef _DEBUG
#pragma comment(lib, "d3dx9d.lib")
#else
#pragma comment(lib, "d3dx9.lib")
#endif

# pragma comment(lib, "winmm.lib")

#include <Windows.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <timeapi.h>
#include <ctime>
#include <stdio.h>     

#include "Global.h"
#include "Camera.h"
#include "InputManager.h"
#include "Transform.h"
#include "DirectX.h"
#include "MeshRender.h"
#include "GameObject.h"
#include "Text.h"
#include "Time.h"
#include "Utils.h"
#include "Button.h"
#include "Sprite.h"
#include "RigidbodyComponent.h"
#include "ColliderComponent.h"
#include "SphereComponent.h"
#include "SphereCollider.h"
#include "Component.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "BulletComponent.h"
#include "CollisionManager.h"

using namespace std;