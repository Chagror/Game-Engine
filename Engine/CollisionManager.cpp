#include "pch.h"
#include "CollisionManager.h"
#include "Engine.h"

void CollisionManager::UpdateCollision(vector<GameObject*> bullets, vector<GameObject*> targets)
{
    for (GameObject* compo : bullets)
    {
        ColliderComponent* firstCollider = compo->GetComponent<ColliderComponent>();
        if (firstCollider != nullptr)
        {
            int i = 0;
            while (i < targets.size())
            {
                compo = targets.at(i);
                ColliderComponent* secCollider = compo->GetComponent<ColliderComponent>();
                if (secCollider != nullptr && secCollider != firstCollider)
                {
                    if (firstCollider->ReactToCollider(secCollider))
                    {
                        DebugLog("COLLISIONS");
                        Transform* secTransform = secCollider->GetParentGO()->GetTransform();
                        firstCollider->Bounce(secTransform);
                        secCollider->GetParentGO()->~GameObject();
                        targets.erase(targets.begin() + i);
                        _score += 100;
                    }
                }
                i++;
            }
        }
    }
    
}

CollisionManager::CollisionManager()
{
    _score = 0;
}

CollisionManager::~CollisionManager()
{
}