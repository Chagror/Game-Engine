#pragma once
#include "MeshComponent.h"

class SphereComponent : public MeshComponent
{
	float _radius;
public:
	SphereComponent(GameObject*);
	~SphereComponent() override = default;

	void CreateSphere(float, uint16_t, uint16_t);
	void Update(float) override;

	float GetRadius() { return _radius; }
};

