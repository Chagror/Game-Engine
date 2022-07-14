#include "pch.h"
#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(GameObject* GO) : Component(GO)
{

}

ColliderComponent::~ColliderComponent()
{
}

bool ColliderComponent::ReactToCollider(ColliderComponent*& other)
{
	return false;
}

void ColliderComponent::Bounce(Transform*& otherTransform)
{
}
