#include "pch.h"
#include "BulletComponent.h"

BulletComponent::BulletComponent(GameObject* GO) : Component(GO)
{
	lifeTime = 2.f;
}

BulletComponent::~BulletComponent()
{
}

void BulletComponent::Update(float deltaTime)
{


	if (lifeTime >= 0) lifeTime -= deltaTime;
}
