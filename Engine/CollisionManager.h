#pragma once
class CollisionManager
{
private:
	int _score;

public:

	CollisionManager();
	~CollisionManager();

	void UpdateCollision(vector<GameObject*>, vector<GameObject*>);

	int GetScore() { return _score; }
};

