#pragma once
class Sprite
{
	LPD3DXSPRITE _sprite;
	LPDIRECT3DTEXTURE9 _spriteTexture;
	std::wstring _fileName;

	D3DXVECTOR3 _center;
	D3DXVECTOR3 _position;
	Transform* _transform;
	float _scale;

public:
	Sprite(D3DXVECTOR3, float);
	~Sprite();

	HRESULT LoadSprite(LPDIRECT3DDEVICE9 pDevice, std::string fileName);
	HRESULT RenderSprite(LPDIRECT3DDEVICE9 pDevice);
	void ReleaseSprite();
	LPD3DXSPRITE GetSprite() { return _sprite;}
	Transform* GetTransform() { return _transform; }
	float GetScale() { return _scale; }
};