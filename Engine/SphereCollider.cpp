#include "pch.h"
#include "SphereCollider.h"
#include "Engine.h"


SphereCollider::SphereCollider(GameObject* GO) : ColliderComponent(GO)
{
    _radius = GO->GetComponent<SphereComponent>()->GetRadius();
}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::Update(float deltaTime)
{

}

bool SphereCollider::ReactToCollider(ColliderComponent*& other)
{
	D3DXVECTOR3 pos = _parentGO->GetTransform()->vPos;
	D3DXVECTOR3 otherPos = other->GetParentGO()->GetTransform()->vPos;
	
	SphereCollider* sphereColl(nullptr);

    sphereColl = dynamic_cast<SphereCollider*>(other);
    if (sphereColl != nullptr)
    {
        //calculate the squared distance
        D3DXVECTOR3 vecDist(otherPos - pos);
        float distSqrt(D3DXVec3Dot(&vecDist, &vecDist));

        //calculate the squared sum of both radius
        float radiusSumSquared(_radius + sphereColl->GetRadius());
        radiusSumSquared *= radiusSumSquared;

        bool temp = distSqrt <= radiusSumSquared;
        return distSqrt <= radiusSumSquared;
    }

	return false;
}

void SphereCollider::Bounce(Transform*& otherTransform)
{
    if (otherTransform == nullptr)
    {
        return;
    }

    D3DXVECTOR3 direction(otherTransform->vPos - _parentGO->GetTransform()->vPos);
    D3DXVECTOR3 normalDirection(0.0f, 0.0f, 0.0f);
    D3DXVec3Normalize(&normalDirection, &direction);

    D3DXVECTOR3 otherUpTransform(otherTransform->vUp);
    D3DXVECTOR3 dot(D3DXVec3Dot(&otherUpTransform, &normalDirection) * otherTransform->vUp);
    D3DXVECTOR3 reflect(normalDirection - dot);

    RigidbodyComponent* rigidbody = _parentGO->GetComponent<RigidbodyComponent>();
    if (rigidbody != nullptr)
    {
        rigidbody->AddForce(-(reflect), 10.f);
    }
}
