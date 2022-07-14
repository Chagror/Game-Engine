#pragma once

class GameObject;

class Component
{
protected:
	GameObject* _parentGO;

public:
	Component(GameObject*);
	virtual ~Component();
	virtual void Update(float);

	//void setParentGO(GameObject*);
	GameObject* GetParentGO() { return _parentGO; }
};

