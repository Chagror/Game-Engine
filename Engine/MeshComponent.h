#pragma once
class MeshComponent : public Component
{
protected:
	LPD3DXMESH _mesh;
	LPD3DXBUFFER _AdjBuffer;

	MeshComponent(GameObject*);
	~MeshComponent() override;

	void Update(float) override;
};

