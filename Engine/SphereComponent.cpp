#include "pch.h"
#include "SphereComponent.h"

SphereComponent::SphereComponent(GameObject* GO): MeshComponent(GO)
{
	
}

void SphereComponent::CreateSphere(float rad, uint16_t slice, uint16_t stack)
{
	_radius = rad;
	D3DXCreateSphere(d3ddev, rad, slice, stack, &_mesh, &_AdjBuffer);

	DWORD* adj = static_cast<DWORD*>(_AdjBuffer->GetBufferPointer());
	_mesh->GenerateAdjacency(FLT_EPSILON, adj);
	_mesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE, adj, nullptr, nullptr, nullptr);
}

void SphereComponent::Update(float deltaTime)
{
	MeshComponent::Update(deltaTime);

	if (_mesh != nullptr) {
		_mesh->DrawSubset(0);
	}
}
