#include "pch.h"
#include "GameObject.h"

//Includes gameobject components
#include "Transform.h"
#include "MeshRender.h"

GameObject::GameObject(Transform* transform)
{
	SetTransform(transform);
}

GameObject::~GameObject()
{
	if (!_components.empty())
	{
		for (auto component : _components)
		{
			delete component;
			component = nullptr;
		}
	}

	/*if (go_transform != nullptr)
	{
		delete go_transform;
		go_transform = nullptr;
	}*/

	/*if (go_mesh != nullptr)
	{
		delete go_mesh;
		go_mesh = nullptr;
	}*/
}




