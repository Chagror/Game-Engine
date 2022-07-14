#pragma once
#include "MeshRender.h"
#include <iostream>
#include <vector>
#include <string>
#include <list>

#include "GameObject.h"
#include "Sprite.h"

struct CUSTOMVERTEX { FLOAT X, Y, Z; D3DVECTOR NORMAL; };
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)

class Text;
class GameObject;

class DirectX
{
private:
	LPDIRECT3D9 _d3d; // the pointer to our Direct3D interface
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer; // the pointer to the vertex buffer
	LPDIRECT3DINDEXBUFFER9 _indexBuffer;

	std::vector<GameObject*>* _gameObjects;
	Text* _fpsText;
	Text* _scoreText;
	Sprite* _hitMarker;

public:
	HINSTANCE hInst; // instance actuelle

	WCHAR szTitle[100]; // Texte de la barre de titre
	WCHAR szWindowClass[100];

	// Fonctions :
	DirectX();
	~DirectX();

	Text* GetFpsText() { return _fpsText; }
	Text* GetScoreText() { return _scoreText; }

	

	void InitD3D(HWND hWnd, string resourcePath);
	static void Init_light(void);
	void Render_frame(Camera*, float);
	BOOL InitInstance(HINSTANCE, int, string);

	GameObject* InstantiateObjectWithMesh(Transform*, Mesh*) const;
	GameObject* InstantiateBullet(Camera*, float, uint16_t, uint16_t) const;
	void InstantiateObjectWithAudio(Transform*, const char*, const char*) const;
	GameObject* InstantiateTarget(Transform tr, float, uint16_t, uint16_t) const;

	Text* TextToDraw(std::string& s, D3DXVECTOR2 pos);
};
