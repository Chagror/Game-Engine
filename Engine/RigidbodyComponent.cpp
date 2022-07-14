#include "pch.h"
#include "RigidbodyComponent.h"

RigidbodyComponent::RigidbodyComponent(GameObject* GO) : Component(GO)
{
	_speed = 30.f;
	_gravity = -4.f;

	_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

RigidbodyComponent::~RigidbodyComponent()
{
}

void RigidbodyComponent::AddForce(D3DXVECTOR3 d, float force)
{
	_dir = d;
	_acceleration = _dir * force;
}

void RigidbodyComponent::Update(float deltaTime)
{
	if (_dir != D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		_acceleration.y += _gravity * deltaTime;

		_parentGO->GetTransform()->Translate(_acceleration.x * deltaTime * _speed, _acceleration.y * deltaTime * _speed, _acceleration.z * deltaTime * _speed);
	}
}