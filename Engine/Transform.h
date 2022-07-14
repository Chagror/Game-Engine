#pragma once
#include "Component.h"

class Transform
{
	

public:
	float pitch;
	float yaw;
	float roll;

	float rotX;
	float rotY;
	float rotZ;

	D3DXVECTOR3 vSca;
	D3DXVECTOR3 vPos;

	D3DXVECTOR3 defaultRight;
	D3DXVECTOR3 defaultForward;

	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vRight;
	D3DXVECTOR3 vUp;

	D3DXMATRIX mRot;
	D3DXMATRIX matrix;

	D3DXQUATERNION qRot;

	Transform();
	Transform(D3DXVECTOR3, D3DXVECTOR3);
	~Transform();

	void Identity();
	//void FromMatrix(D3DMATRIX* pMat);
	//void UpdateRotationFromVector();
	void UpdateRotationFromQuaternion();
	void UpdateMatrix();
	void Rotate(float yaw, float pitch, float roll);
	void Translate(float x,float y, float z);
	void RotateYaw(float angle);
	void RotatePitch(float angle);
	void RotateRoll(float angle);
	//void RotateWorld(D3DMATRIX);
	void RotateWorldX(float angle);
	void RotateWorldY(float angle);
	void RotateWorldZ(float angle);
	void RescaleMatrix(D3DXVECTOR3);
	void TranslateMatrix(D3DXVECTOR3);
	void SetRotation(float, float, float);
	void ChangePosition(D3DXVECTOR3);
};



