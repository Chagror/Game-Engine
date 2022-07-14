#include "pch.h"
#include "DirectX.h"
#include "Text.h"
#include "GameObject.h"
#include "framework.h"
#include <string>

#include "SphereComponent.h"

DirectX::DirectX()
{
    _d3d = nullptr;
    _vertexBuffer = nullptr;
    _indexBuffer = nullptr;
    
    _gameObjects = new std::vector<GameObject*>;
    _hitMarker = new Sprite(D3DXVECTOR3((SCREEN_WIDTH * 0.5), (SCREEN_HEIGHT * 0.5), 0), 0.1f);

    //textToDraw = new std::list<Text*>;
;}

DirectX::~DirectX()
{
    if (_hitMarker != nullptr)
    {
        _hitMarker->ReleaseSprite();
        delete _hitMarker;
    }

    if (d3ddev != nullptr) d3ddev->Release();    // close and release the 3D device
    if (_d3d != nullptr) _d3d->Release();    // close and release Direct3D

    if (_vertexBuffer != nullptr) _vertexBuffer->Release();
    if (_indexBuffer != nullptr) _indexBuffer->Release();

    if (_gameObjects != nullptr)
    {
        if (!_gameObjects->empty())
        {
            for (GameObject* GO : *_gameObjects)
            {
                delete GO;
            }
        }

        delete _gameObjects;
        _gameObjects = nullptr;
    }

    if (_fpsText != nullptr)
    {
        delete _fpsText;
        _fpsText = nullptr;
    }

    if (_scoreText != nullptr)
    {
        delete _scoreText;
        _scoreText = nullptr;
    }
}

/// <summary>
/// Saves the instance handle and creates a main window
/// </summary>
/// <returns> Bool if the function work </returns>
BOOL DirectX::InitInstance(HINSTANCE hInstance, int nCmdShow, string resourcePath)
{
    hInst = hInstance; // Stocke le handle d'instance dans la variable globale

    const HWND temphWnd = CreateWindowW(szWindowClass, szTitle, WS_EX_TOPMOST | WS_POPUP,
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr);

    const HMONITOR monitor = MonitorFromWindow(temphWnd, MONITOR_DEFAULTTONEAREST);

    DestroyWindow(temphWnd);

    MONITORINFO info;
    info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(monitor, &info);
    int newScreenWidth = info.rcMonitor.right - info.rcMonitor.left;
    int newScreenHeight = info.rcMonitor.bottom - info.rcMonitor.top;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_EX_TOPMOST | WS_POPUP,
        0, 0, newScreenWidth, newScreenHeight, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);

    // set up and initialize Direct3D
    InitD3D(hWnd, resourcePath);
    UpdateWindow(hWnd);

    return TRUE;
}

/// <summary>
/// Instantiate GameObject with mesh
/// </summary>
/// <param name="transform"> GameObject scene transform </param>
/// <param name="mesh"> GameObject mesh </param>
/// <returns> GameObject with mesh </returns>
GameObject* DirectX::InstantiateObjectWithMesh(Transform* transform, Mesh* mesh) const
{
    GameObject* gameobject = new GameObject(transform);
	MeshRender* tempMesh = gameobject->AddComponent<MeshRender>();

    if (tempMesh == nullptr)
    {
        delete gameobject;
        return nullptr;
    }

    tempMesh->SetMesh(mesh);

    _gameObjects->push_back(gameobject);

    return gameobject;
}

/// <summary>
/// Instantiate bullet GameObject
/// </summary>
/// <param name="cam"> Player camera to spawn bullet </param>
/// <param name="radius"> Radius of the bullet sphere </param>
/// <param name="slice"> Number of sphere slice </param>
/// <param name="stack"> Number of sphere slice stack </param>
/// <returns> Bullet GameObject </returns>
GameObject* DirectX::InstantiateBullet(Camera* cam, float radius, uint16_t slice, uint16_t stack) const
{
    Transform tr((cam->GetCamTarget()), D3DXVECTOR3(1, 1, 1));

    GameObject* gameobject = new GameObject(&tr);
    D3DXVECTOR3 dir = gameobject->GetTransform()->vPos - cam->GetTransform()->vPos;
    //D3DXVec3Normalize(&dir ,&dir);   

	SphereComponent* tempSphere = gameobject->AddComponent<SphereComponent>();
    RigidbodyComponent* tempRigidbody = gameobject->AddComponent<RigidbodyComponent>();


    if(tempRigidbody != nullptr)
        tempRigidbody->AddForce(dir, 18.f);

    if (tempSphere == nullptr)
    {
        delete gameobject;
        return nullptr;
    }

    tempSphere->CreateSphere(radius, slice, stack);

	SphereCollider* tempSphereCollider = gameobject->AddComponent<SphereCollider>();
    auto* tempBullet = gameobject->AddComponent<BulletComponent>();

    if (tempBullet == nullptr || tempSphereCollider == nullptr)
    {
        delete gameobject;
        return nullptr;
    }

    _gameObjects->push_back(gameobject);

    return gameobject;
}


/// <summary>
/// Instantiate target game object
/// </summary>
/// <param name="tr"> Game object transform </param>
/// <param name="radius"> Spehere radius </param>
/// <param name="slice"></param>
/// <param name="stack"></param>
GameObject* DirectX::InstantiateTarget(Transform tr, float radius, uint16_t slice, uint16_t stack) const
{
    GameObject* gameobject = new GameObject(&tr);

    SphereComponent* tempSphere = gameobject->AddComponent<SphereComponent>();

    if (tempSphere == nullptr)
    {
        delete gameobject;
        return nullptr;
    }

    tempSphere->CreateSphere(radius, slice, stack);

    SphereCollider* tempSphereCollider = gameobject->AddComponent<SphereCollider>();

    if (tempSphereCollider == nullptr)
    {
        delete gameobject;
        return nullptr;
    }    
    _gameObjects->push_back(gameobject);

    return gameobject;
}

/// <summary>
/// This function initializes and prepares Direct3D for use
/// </summary>
void DirectX::InitD3D(HWND hWnd, string resourcePath)
{
    _d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

    D3DPRESENT_PARAMETERS d3dpp = {};    // create a struct to hold various device information

    d3dpp.Windowed = TRUE;    // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
    d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;    // set the back buffer format to 32-bit
    d3dpp.BackBufferWidth = SCREEN_WIDTH;    // set the width of the buffer
    d3dpp.BackBufferHeight = SCREEN_HEIGHT;    // set the height of the buffer
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
    d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

    // create a device class using this information and the info from the d3dpp stuct
    _d3d->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp,
        &d3ddev);

    Init_light();       // call the function to initialize the light and material

    d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);    // turn off the 3D lighting
    d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // both sides of the triangles
    d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
    d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));    // ambient light

    //PlaySound
    auto tempSoundPath = resourcePath + "music.wav";
    PlaySoundA(tempSoundPath.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    
   
    // Init Sprite
    auto tempSpritePath = resourcePath + "hitmarker.png";
    _hitMarker->LoadSprite(d3ddev, tempSpritePath);

    // Init FPS Text
    std::string s = "FPS : " + std::to_string(0);
    _fpsText = TextToDraw(s, D3DXVECTOR2(0, 0));

    // Init Score Text
    std::string s2 = "Score : " + std::to_string(0);
    _scoreText = TextToDraw(s2, D3DXVECTOR2(0, 15));
}

/// <summary>
/// This is the function that sets up the lights and materials
/// </summary>
void DirectX::Init_light()
{
    D3DLIGHT9 light;    // create the light struct
    D3DMATERIAL9 material;    // create the material struct

    memset(&light, 0, sizeof(light));    // clear out the light struct for use
    light.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
    light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);    // set the light's color
    light.Direction = D3DXVECTOR3(-1.0f, -0.3f, -1.0f);

    d3ddev->SetLight(0, &light);    // send the light struct properties to light #0
    d3ddev->LightEnable(0, TRUE);    // turn on light #0

    memset(&material, 0, sizeof(D3DMATERIAL9));    // clear out the struct for use
    material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
    material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

    d3ddev->SetMaterial(&material);    // set the globably-used material to &material
}


D3DXVECTOR3 va = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
D3DXVECTOR3 vb = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
D3DXVECTOR3 vc = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
D3DXVECTOR3 vd = D3DXVECTOR3(0.00f, 0.33f, 0.67f);
float progress;

/// <summary>
/// This is the function used to render a single frame
/// </summary>
/// <param name="cam"> Game camera </param>
/// <param name="deltaTime"> DeltaTime </param>
void DirectX::Render_frame(Camera* cam, float deltaTime)
{    
    D3DXVECTOR3 result = palette(progress, va, vb, vc, vd) * 255.0f;
    progress += 0.2f * deltaTime;

    while (progress >= 1.0f)
        progress -= 1.0f;

    float r = result.x;
    float g = result.y;
    float b = result.z;

    // clear the window to a deep blue
    d3ddev->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(static_cast<int>(r), static_cast<int>(g), static_cast<int>(b)), 1.0f, 0);

    d3ddev->BeginScene();    // begins the 3D scene

    // select which vertex format we are using
    d3ddev->SetFVF(CUSTOMFVF);

    // SET UP THE PIPELINE

    cam->UpdateCamera();

    D3DXMATRIX matProjection;     // the projection transform matrix
    D3DXMatrixPerspectiveFovLH(&matProjection,
        D3DXToRadian(45),    // the horizontal field of view
        static_cast<FLOAT>(1920) / static_cast<FLOAT>(1080), // aspect ratio
        0.1f,    // the near view-plane
        200.0f);    // the far view-plane
    d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

    _hitMarker->RenderSprite(d3ddev);

    _fpsText->Draw();
    _scoreText->Draw();

    if (!_gameObjects->empty())
    {
    	int i = 0;

        while (i < _gameObjects->size())
        {
            GameObject* GO = _gameObjects->at(i);            

            const auto tr = GO->GetTransform();
            if (tr != nullptr)
                d3ddev->SetTransform(D3DTS_WORLD, &tr->matrix);

            const auto mesh = GO->GetComponent<MeshRender>();
            if (mesh != nullptr) mesh->Update(deltaTime, 2, 2);

            const auto bullet = GO->GetComponent<BulletComponent>();
            const auto sphere = GO->GetComponent<SphereComponent>();            

            if (sphere != nullptr)
            {
                sphere->Update(deltaTime);
            }
            if (bullet != nullptr)
            {
                bullet->Update(deltaTime);

                if (bullet->lifeTime <= 0)
                {
                    _gameObjects->erase(_gameObjects->begin() + i);
                    //bullet->~Bullet();
                    //delete GO;

                }
            }

            const auto rigidbody = GO->GetComponent<RigidbodyComponent>();

            if (rigidbody != nullptr) 
            {
                rigidbody->Update(deltaTime);
            }
            i++;
        }
    }
    
	d3ddev->EndScene();    // ends the 3D scene
	d3ddev->Present(nullptr, nullptr, nullptr, nullptr);   // displays the created frame on the screen
}

/// <summary>
/// Create Text pointer
/// </summary>
/// <param name="s"> Text to draw </param>
/// <returns> Text pointer </returns>
Text* DirectX::TextToDraw(std::string& s, D3DXVECTOR2 pos)
{
    std::wstring temp(s.begin(), s.end());
    LPCWSTR lpcwstr = temp.c_str();
    Text* test = new Text(lpcwstr, D3DXCOLOR(255, 255, 255, 1), pos);
    return test;
}
