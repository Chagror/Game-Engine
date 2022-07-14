#pragma once
#include "Component.h"

class RigidbodyComponent :
    public Component
{
	float _speed;
	float _gravity;

	D3DXVECTOR3 _acceleration;

	D3DXVECTOR3 _dir;

public:

	RigidbodyComponent(GameObject*);
	~RigidbodyComponent() override;

	void Update(float) override;
	void AddForce(D3DXVECTOR3, float);
};

