#pragma once

struct MeshVertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 texCoord;
};

class Mesh
{
private:
	const char* _strPrefix = "..\\";

	DWORD _num{};

	LPD3DXMESH _pMesh;
	LPDIRECT3DTEXTURE9* _pTex;
	D3DMATERIAL9* _pMaterial;

public:
	Mesh();
	Mesh(const char* catalog, const char* filename);
	~Mesh();

	DWORD GetNumMat() const { return _num; }
	LPD3DXMESH GetMesh() const { return _pMesh; }
	LPDIRECT3DTEXTURE9* GetTex() const { return _pTex; }
	D3DMATERIAL9* GetMat() const { return _pMaterial; }
};
