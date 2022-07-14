#include "pch.h"
#include "Component.h"

Component::Component(GameObject* GO)
{
	if(_parentGO == nullptr)
		_parentGO = GO;
}

Component::~Component()
{
}

void Component::Update(float deltaTime)
{
}

//void Component::setParentGO(GameObject* GO)
//{
//	parentGO = GO;
//}
