#include "pch.h"
#include "Mesh.h"

Mesh::Mesh()
{
	_pTex = nullptr;
	_pMaterial = nullptr;
}

Mesh::Mesh(const char* catalog, const char* filename)
{
	_pMesh = nullptr;
	_pTex = nullptr;
	_pMaterial = nullptr;

	ID3DXBuffer* pMrtlBuffer = nullptr;

	char filepath[MAX_PATH];

	strncpy_s(filepath, MAX_PATH, catalog, strlen(catalog));
	strncat_s(filepath, MAX_PATH, filename, strlen(filename));

	if (FAILED(D3DXLoadMeshFromXA(filepath, D3DXMESH_MANAGED, d3ddev, nullptr, &pMrtlBuffer, NULL, &_num, &_pMesh)))
	{
		char strFile[MAX_PATH];
		strcpy_s(strFile, MAX_PATH, _strPrefix);
		strcat_s(strFile, MAX_PATH, filepath);

		if (FAILED(D3DXLoadMeshFromXA(strFile, D3DXMESH_MANAGED, d3ddev, nullptr, &pMrtlBuffer, NULL, &_num, &_pMesh)))
		{
			MessageBox(nullptr, L"Load mesh fail", nullptr, 0);
			return;
		}
	}

	const D3DXMATERIAL* pMtrls = static_cast<D3DXMATERIAL*>(pMrtlBuffer->GetBufferPointer());

	_pMaterial = new D3DMATERIAL9[_num];
	_pTex = new LPDIRECT3DTEXTURE9[_num];

	if (_pMaterial == nullptr || _pTex == nullptr)
		return;

	for (DWORD i = 0; i < _num; i++)
	{
		_pTex[i] = nullptr;

		_pMaterial[i] = pMtrls[i].MatD3D;
		_pMaterial[i].Ambient = _pMaterial[i].Diffuse;

		if (pMtrls[i].pTextureFilename == nullptr || lstrlenA(pMtrls[i].pTextureFilename) <= 0) continue;

		strncpy_s(filepath, MAX_PATH, catalog, strlen(catalog));
		strncat_s(filepath, MAX_PATH, pMtrls[i].pTextureFilename, strlen(pMtrls[i].pTextureFilename));

		// Create the texture
		if (FAILED(D3DXCreateTextureFromFileA(d3ddev, filepath, &_pTex[i])))
		{
			// If texture is not in current folder, try parent folder
			char strTexture[MAX_PATH];
			strcpy_s(strTexture, MAX_PATH, _strPrefix);
			strcat_s(strTexture, MAX_PATH, catalog);
			strcat_s(strTexture, MAX_PATH, pMtrls[i].pTextureFilename);

			// If texture is not in current folder, try parent folder
			if (FAILED(D3DXCreateTextureFromFileA(d3ddev, strTexture, &_pTex[i])))
			{
				MessageBox(nullptr, L"Could not find texture map", L"Meshes.exe", MB_OK);
			}
		}
	}

	//const DWORD* adj = static_cast<DWORD*>(pAdjBuffer->GetBufferPointer());
	
	DWORD* adj = new DWORD[_pMesh->GetNumFaces() * 3];
	_pMesh->GenerateAdjacency(FLT_EPSILON, adj);
	_pMesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE, adj, nullptr, nullptr, nullptr);

	pMrtlBuffer->Release();

	if (adj != nullptr)
	{
		delete adj;
		adj = nullptr;
	}
}

Mesh::~Mesh()
{
	if (_pMaterial != nullptr)
	{
		delete _pMaterial;
		_pMaterial = nullptr;
	}

	if (_pMesh != nullptr)
	{
		_pMesh->Release();
	}

	if (&_pTex != nullptr)
	{
		for (DWORD i = 0; i < _num; ++i)
		{
			if (_pTex[i])
			{
				_pTex[i]->Release();
			}
		}

		delete _pTex;
		_pTex = nullptr;
	}
}
