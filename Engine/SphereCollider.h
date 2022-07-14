#pragma once
#include "ColliderComponent.h"
class SphereCollider :
    public ColliderComponent
{
    float _radius;

public:
    SphereCollider(GameObject* GO);
    ~SphereCollider();

    void Update(float deltaTime) override;

    bool ReactToCollider(ColliderComponent*& other) override;
    void Bounce(Transform*& otherTransform);

    float GetRadius() { return _radius; }
};

