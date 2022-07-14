#include "pch.h"
#include "Sprite.h"

Sprite::Sprite(D3DXVECTOR3 _pos, float _sca)
{
	_sprite = NULL;
	_spriteTexture = NULL;
	_center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_position = _pos/_sca;
	_scale = _sca;
	_transform = new Transform(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(_sca,_sca,_sca));
}

Sprite::~Sprite()
{
	if (_spriteTexture != nullptr)
	{
		delete _spriteTexture;
		_spriteTexture = nullptr;
	}
	if (_sprite != nullptr)
	{
		delete _sprite;
		_sprite = nullptr;
	}
}

HRESULT Sprite::LoadSprite(LPDIRECT3DDEVICE9 pDevice, std::string fileName)
{
	if (!pDevice)
	{
		return -1;
	}

	if (this->_sprite)
	{
		_sprite->Release();
	}

	if (this->_spriteTexture)
	{
		this->_spriteTexture->Release();
		this->_spriteTexture = NULL;
	}

	D3DXCreateSprite(pDevice, &_sprite);
	//create a texture surface from a file
	std::wstring temp(fileName.begin(), fileName.end());
	HRESULT result = D3DXCreateTextureFromFile(pDevice, temp.c_str(), &_spriteTexture);
	D3DSURFACE_DESC surfaceDesc;
	_spriteTexture->GetLevelDesc(0, &surfaceDesc);
	_center = D3DXVECTOR3(surfaceDesc.Height*0.5, surfaceDesc.Width*0.5, 0.0f);
	if (FAILED(result))
	{
		MessageBox(nullptr, L"Load sprite fail", nullptr, 0);
		return -1;
	}
	return 0;
}

HRESULT Sprite::RenderSprite(LPDIRECT3DDEVICE9 pDevice)
{
	if (!pDevice)
	{
		return -1;
	}
	this->_sprite->Begin(D3DXSPRITE_ALPHABLEND);
	this->_sprite->SetTransform(&this->_transform->matrix);

	HRESULT result;
	result = this->_sprite->Draw(this->_spriteTexture, NULL, &_center, &_position, D3DCOLOR_XRGB(255, 255, 255));
	this->_sprite->End();

	if (FAILED(result))
	{
		return -1;
	}
	return 0;
}

void Sprite::ReleaseSprite()
{
	if (_sprite)
	{
		this->_sprite->Release();
	}
	_sprite = 0;

	if (_spriteTexture)
	{
		this->_spriteTexture->Release();
	}
	_spriteTexture = 0;
}
