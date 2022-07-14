// RollerCoaster.cpp : Définit le point d'entrée de l'application.
//

#include "framework.h"
#include "RollerCoaster.h"
#include <math.h>
#include <time.h>

#include <algorithm>
#include <regex>

#define MAX_LOADSTRING 100

int isPlaying = true;

Time* m_Time = nullptr;
DirectX* m_directX = nullptr;
Camera* m_camera = nullptr;
InputManager* m_inputManager = nullptr;
CollisionManager* m_collisionManager = nullptr;
float railWitdh = 30;
float speed = 4;

vector<GameObject*> rails;
vector<GameObject*> targets;
vector<GameObject*> bullets;

D3DXVECTOR3 endPosLastRail;
D3DXVECTOR3 posLastRail;

float baseTargetSpawnCooldown = .8f;
float cooldownSpawnTarget = baseTargetSpawnCooldown;

float baseCooldown = .5f;
float cooldown = .0f;

//string ressourcePath;

// Déclarations anticipées des fonctions incluses dans ce module de code :
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

bool UpdateTime() {
    bool tempTick = m_Time->Tick();
    if (tempTick) 
    {
        std::string s = "FPS : " + std::to_string(m_Time->GetFps());
        std::wstring temp(s.begin(), s.end());
        LPCWSTR lpcwstr = temp.c_str();
        m_directX->GetFpsText()->SetText(lpcwstr);
    }
    return tempTick;
}

/// <summary>
/// Generate target with random rate
/// </summary>
/// <param name="basePos"> Base rail position to spawn target near this </param>
void GenerateTargets(D3DXVECTOR3 basePos)
{
    if (cooldownSpawnTarget > 0)
    {        
        return;
    }

    int randomNumber = rand() % 5;

    if (randomNumber == 2)
    {
        int randomX = rand() % 50 + 30;
        int randomY = rand() % 10 + 20;
        Transform tr(D3DXVECTOR3(basePos.x + randomX, basePos.y + randomY, basePos.z), D3DXVECTOR3(1.f, 1.f, 1.f));
        GameObject* go = m_directX->InstantiateTarget(tr, 5.f, 20, 20);
        targets.push_back(go);
        cooldownSpawnTarget = baseTargetSpawnCooldown;
    }

    if (randomNumber == 3)
    {
        int randomX = rand() % 50 + 30;
        int randomY = rand() % 10 + 20;
        Transform tr(D3DXVECTOR3(basePos.x - randomX, basePos.y + randomY, basePos.z), D3DXVECTOR3(1.f, 1.f, 1.f));
        GameObject* go = m_directX->InstantiateTarget(tr, 5.f, 20, 20);
        targets.push_back(go);
        cooldownSpawnTarget = baseTargetSpawnCooldown;
    }
     
    if (targets.size() > 5)
    {
        targets[0]->~GameObject();
        targets.erase(targets.begin());
    }
}

void GenerateBullets()
{
    if (cooldown >= baseCooldown)
    {
        GameObject* tempBullet = m_directX->InstantiateBullet(m_camera, 1.35f, 20, 20);

        cooldown = 0.f;
        bullets.push_back(tempBullet);
    }
}

void Loop(MSG msg, string resourcePath) {

    char meshPath[MAX_PATH];
    strncpy_s(meshPath, MAX_PATH, resourcePath.c_str(), strlen(resourcePath.c_str()));
    strncat_s(meshPath, MAX_PATH, "rail\\", strlen("rail\\"));

    Mesh tempMesh(meshPath, "rail.x");

    for (int i = 0; rails.size() < 9; i++)
    {
        Transform tr(D3DXVECTOR3(1, 1, i * railWitdh), D3DXVECTOR3(0.1, 0.1, 0.1));
        GameObject* go = m_directX->InstantiateObjectWithMesh(&tr, &tempMesh);
        rails.push_back(go);        
    }

    D3DXVECTOR3 dirRail = D3DXVECTOR3(0, sinf(D3DXToRadian(rails[8]->GetTransform()->rotY)), cosf(D3DXToRadian(rails[8]->GetTransform()->rotZ)) * cosf(D3DXToRadian(rails[8]->GetTransform()->rotY)));
    endPosLastRail = rails[8]->GetTransform()->vPos;
    endPosLastRail += dirRail * 0.45f * 30;

    while (isPlaying)
    {
        Sleep(1);


        bool isTicking = UpdateTime();

        if (!isTicking) continue;

        
        if (m_camera->reachDestination)
        {
            int randomNumber = rand() % 6;
            float angle = -0.5;
            m_camera->ChangeTarget(rails[2]->GetTransform()->vPos);
            rails[0]->~GameObject();
            rails.erase(rails.begin());

            Transform tr(D3DXVECTOR3(1, 1, rails[7]->GetTransform()->vPos.z), D3DXVECTOR3(0.1, 0.1, 0.1));

            //Rotation
            float rotationZ = ((rand() % 21) - 10);
            float rotationY = ((rand() % 21) - 10);
            tr.rotZ += rotationZ;
            tr.rotY += rotationY;

            dirRail = D3DXVECTOR3(sinf(D3DXToRadian(tr.rotZ)) * cosf(D3DXToRadian(tr.rotY)),
                sinf(D3DXToRadian(tr.rotY)), cosf(D3DXToRadian(tr.rotZ)) * cosf(D3DXToRadian(tr.rotY)));

            posLastRail = endPosLastRail + +dirRail * 0.45f * 30;

            tr.ChangePosition(posLastRail);

            tr.SetRotation(D3DXToRadian(tr.rotZ), D3DXToRadian(-tr.rotY), 0);
            
            endPosLastRail = posLastRail + +dirRail * 0.45f * 30;

            GameObject* go = m_directX->InstantiateObjectWithMesh(&tr, &tempMesh);

            rails.push_back(go);
            GenerateTargets(go->GetTransform()->vPos);
            
        }

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

        }

        if (msg.message == WM_QUIT)
        {
            isPlaying = false;
            break;
        }

        if (cooldownSpawnTarget > 0) cooldownSpawnTarget -= m_Time->GetDeltaTime();
        if (cooldown <= baseCooldown) cooldown += m_Time->GetDeltaTime();

        m_inputManager->CheckInput(m_Time->GetDeltaTime(), m_camera, m_directX);
    	m_directX->Render_frame(m_camera, m_Time->GetDeltaTime());
        m_collisionManager->UpdateCollision(bullets, targets);

        std::string s = "Score : " + std::to_string(m_collisionManager->GetScore());
        std::wstring tempWString(s.begin(), s.end());
        LPCWSTR lpcwstr = tempWString.c_str();
        m_directX->GetScoreText()->SetText(lpcwstr);
    }
}

//Main
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialise les chaînes globales
    m_Time = new Time();
    m_directX = new DirectX();
    m_camera = new Camera();
    m_inputManager = new InputManager();
    m_collisionManager = new CollisionManager();

    LoadStringW(hInstance, IDS_APP_TITLE, m_directX->szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ROLLERCOASTER, m_directX->szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    auto resourcePath = static_cast<string>(GetCommandLineA());
    size_t pos = resourcePath.find("RollerCoaster.exe");
    resourcePath = resourcePath.substr(1, pos-1);
    resourcePath += "Resource\\";

    // Effectue l'initialisation de l'application :
    if (!m_directX->InitInstance(hInstance, nCmdShow, resourcePath) && !m_inputManager->InitializeInput())
    {
        return FALSE;
    }

    m_camera->reachDestination = true;

    // enter the main loop:

    MSG msg{};

    srand((unsigned int)time(0));
    

    ShowCursor(false);

    Loop(msg, resourcePath);

    delete m_Time;
    delete m_directX;
    delete m_camera;
    delete m_inputManager;

    const HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROLLERCOASTER));

    // Boucle de messages principale :
    /*while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/

    return static_cast<int>(msg.wParam);
}

//
//  FONCTION : MyRegisterClass()
//
//  OBJECTIF : Inscrit la classe de fenêtre.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROLLERCOASTER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+3);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = m_directX->szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//  FONCTION : WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  OBJECTIF : Traite les messages pour la fenêtre principale.
//
//  WM_COMMAND  - traite le menu de l'application
//  WM_PAINT    - Dessine la fenêtre principale
//  WM_DESTROY  - génère un message d'arrêt et retourne
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
	    {
	        //delete m_camera;
	        PostQuitMessage(0);
	        break;
	    }
    case WM_MOUSEMOVE:
    {
        D3DXVECTOR2 centerPoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        POINT p = { 0, 0 };
        ::GetCursorPos(&p);
        ::ScreenToClient(hWnd, &p);
        D3DXVECTOR2 cPos(p.x, p.y);

        D3DXVECTOR2 result(p.x - centerPoint.x, p.y - centerPoint.y);
        
        float norme = sqrt(result.x * result.x + result.y * result.y);
        if (norme != 0) {
            result.x = result.x / norme;
            result.y = result.y / norme;
        }
        m_camera->GetTransform()->pitch += result.x * m_Time->GetDeltaTime() * speed;
        float cameraLockY = m_camera->GetTransform()->yaw + result.y * m_Time->GetDeltaTime() * speed;
        if (cameraLockY <= 1.f && cameraLockY >= -1.f) {
            m_camera->GetTransform()->yaw += result.y * m_Time->GetDeltaTime() * speed;
        }
        //DebugLog("Camera : " + std::to_string(m_camera->getTransform()->yaw));
        SetCursorPos(centerPoint.x, centerPoint.y);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        GenerateBullets();
    }
    case WM_INPUT:
    {
        if (::GetAsyncKeyState('L') & 0x8000f)
        {
            DebugLog("ici");
            rails[1]->GetTransform();

            rails[1]->GetTransform()->SetRotation(0,-0.5,0);
            rails[1]->GetTransform()->Translate(0,7,0);
            int a = 0;
        }
        
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}






