#include "pch.h"
#include "MeshRender.h"

#include "GameObject.h"

MeshRender::MeshRender(GameObject* GO) : MeshComponent(GO)
{
}

MeshRender::~MeshRender()
{
}

void MeshRender::SetMesh(Mesh* newMesh)
{
	_mesh = newMesh;
}

void MeshRender::Update(float deltaTime)
{
	MeshComponent::Update(deltaTime);

	if (_mesh->GetMesh() == nullptr) return;

	for (DWORD i = 0; i < _mesh->GetNumMat(); ++i)
	{
		D3DMATERIAL9* mat = _mesh->GetMat();
		LPDIRECT3DTEXTURE9* tex = _mesh->GetTex();

		if (&mat[i])
		{
			d3ddev->SetMaterial(&mat[i]);
		}
		else
		{
			D3DMATERIAL9 mtrl{};
			mtrl.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			mtrl.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			mtrl.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			mtrl.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			mtrl.Power = 2.0f;

			d3ddev->SetMaterial(&mtrl);
		}

		if (_mesh->GetTex() == nullptr) continue;

		if (tex[i] != nullptr)
		{
			d3ddev->SetTexture(0, tex[i]);
		}
		else
		{
			d3ddev->SetTexture(0, nullptr);
		}

		_mesh->GetMesh()->DrawSubset(i);
	}
}

void MeshRender::Update(float deltaTime, uint8_t min, uint8_t max)
{
	MeshComponent::Update(deltaTime);

	if (_mesh->GetMesh() == nullptr || max >= _mesh->GetNumMat()) return;

	for (DWORD i = min; i <= max; ++i)
	{
		D3DMATERIAL9* mat = _mesh->GetMat();
		LPDIRECT3DTEXTURE9* tex = _mesh->GetTex();

		if (&mat[i])
		{
			d3ddev->SetMaterial(&mat[i]);
		}
		else
		{
			D3DMATERIAL9 mtrl{};
			mtrl.Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			mtrl.Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			mtrl.Specular = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			mtrl.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			mtrl.Power = 2.0f;

			d3ddev->SetMaterial(&mtrl);
		}

		if (tex[i] != nullptr)
		{
			d3ddev->SetTexture(0, tex[i]);
		}
		else
		{
			d3ddev->SetTexture(0, nullptr);
		}

		_mesh->GetMesh()->DrawSubset(i);
	}
}
