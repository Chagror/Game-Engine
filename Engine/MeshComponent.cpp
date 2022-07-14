#include "pch.h"
#include "MeshComponent.h"

MeshComponent::MeshComponent(GameObject* GO) : Component(GO)
{
	_mesh = nullptr;
	_AdjBuffer = nullptr;

}

MeshComponent::~MeshComponent()
{
	if (_mesh != nullptr)
	{
		_mesh->Release();
	}

	if (_AdjBuffer != nullptr)
	{
		_AdjBuffer->Release();
	}
}

void MeshComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);
}
