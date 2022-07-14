#pragma once

class Transform;
class Mesh;

class GameObject
{
public:
	GameObject(Transform*);
	~GameObject();

private:

	//Components
	Transform _transform;
	vector<Component*> _components;

public:
	//Getter
	Transform* GetTransform() { return &_transform; }

	//Setter
	void SetTransform(Transform* transform) { _transform = *transform; }

	template<class T>
	T* AddComponent();

	template<class T>
	T* GetComponent();

	//void Update(float deltaTime);
};

template <class T>
T* GameObject::AddComponent()
{
	if (is_base_of_v<Component, T>)
	{
		T* p = new T(this);
		_components.push_back(p);
		return p;
	}

	return nullptr;
}

template <class T>
T* GameObject::GetComponent()
{
	for (auto it = _components.begin(); it != _components.end(); ++it)
	{
		T* temp = dynamic_cast<T*>(*it);

		if (temp != nullptr) return temp;
	}

	return nullptr;
}
