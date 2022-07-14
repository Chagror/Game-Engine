#pragma once
class BulletComponent : public Component
{
public:
	float lifeTime;

	BulletComponent(GameObject*);
	~BulletComponent() override;

	void Update(float deltaTime) override;
};

