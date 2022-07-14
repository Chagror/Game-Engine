#pragma once
#include "Component.h"

class Transform;

class ColliderComponent :
    public Component
{
public:
    ColliderComponent(GameObject* GO);
    ~ColliderComponent() override;

    virtual bool ReactToCollider(ColliderComponent*& other);
    virtual void Bounce(Transform*& otherTransform);
};

