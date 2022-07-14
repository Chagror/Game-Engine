#pragma once
#include "Component.h"
#include "Mesh.h"
#include "MeshComponent.h"

using namespace std;

class MeshRender: public MeshComponent
{
private:
	Mesh* _mesh;

public:
	MeshRender(GameObject*);
	~MeshRender() override;

	void SetMesh(Mesh* newMesh);

	void Update(float) override;
	void Update(float, uint8_t min, uint8_t max);
};
