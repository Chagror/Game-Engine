#include "pch.h"
#include "Transform.h"

Transform::Transform()
{
	Identity();
}

Transform::Transform(D3DXVECTOR3 _Pos, D3DXVECTOR3 _Sca)
{
	Identity();
	vPos = _Pos;
	vSca = _Sca;
	rotY = 0;
	rotZ = 0;
	UpdateMatrix();
}

Transform::~Transform()
{
}

void Transform::Identity() {
	D3DXMatrixIdentity(&matrix);
	D3DXMatrixIdentity(&mRot);
	D3DXQuaternionIdentity(&qRot);

	vSca = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vDir = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	vRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	defaultRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	defaultForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;
	UpdateMatrix();
}

void Transform::UpdateRotationFromQuaternion()
{
	// Convertir le quaternion en une matrice de rotation (magique)
	D3DXMatrixRotationQuaternion(&mRot, &qRot);
	UpdateMatrix();
}

void Transform::UpdateMatrix()
{
	D3DXMATRIX mtmpScal;
	D3DXMATRIX mtmpPos;

	D3DXMatrixScaling(&matrix, vSca.x, vSca.y, vSca.z);
	//D3DXMatrixTranslation(&mtmpPos, vPos.x, vPos.y ,vPos.z);
	//D3DXMatrixMultiply(&matrix, &mtmpScal, &mtmpPos);
	matrix *= mRot;
	matrix._41 = vPos.x;
	matrix._42 = vPos.y;
	matrix._43 = vPos.z;
}

void Transform::Rotate(const float yaw, const float pitch, const float roll) {
	//Créer le quaternion de rotation
	D3DXQUATERNION _qRot;
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &vUp, pitch);
	_qRot *= quat;
	D3DXQuaternionRotationAxis(&quat, &vRight, yaw);
	_qRot *= quat;
	D3DXQuaternionRotationAxis(&quat, &vDir, roll);
	_qRot *= quat;

	// Ajouter la rotation delta � la rotation actuelle de l�objet
	qRot *= _qRot;

	//Remplir la matrice de rotation avec le quaternion
	D3DXMatrixRotationQuaternion(&mRot, &qRot);
	vRight.x = mRot._11;
	vRight.y = mRot._12;
	vRight.z = mRot._13;
	vUp.x = mRot._21;
	vUp.y = mRot._22;
	vUp.z = mRot._23;
	vDir.x = mRot._31;
	vDir.y = mRot._32;
	vDir.z = mRot._33;
	UpdateMatrix();
}

void Transform::Translate(const float x, const float y, const float z)
{
	vPos.x += x;
	vPos.y += y;
	vPos.z += z;

	UpdateMatrix();
}

void Transform::RotateYaw(const float angle)
{
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &vUp, angle);
	qRot *= quat;
	UpdateRotationFromQuaternion();
}

void Transform::RotatePitch(const float angle)
{
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &vRight, angle);
	qRot *= quat;
	UpdateRotationFromQuaternion();
}

void Transform::RotateRoll(const float angle)
{
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &vDir, angle);
	qRot *= quat;
	UpdateRotationFromQuaternion();
}

void Transform::RotateWorldX(const float angle)
{
	D3DXMatrixRotationX(&mRot, angle);
	UpdateMatrix();
}

void Transform::RotateWorldY(const float angle)
{
	D3DXMatrixRotationY(&mRot, angle);
	UpdateMatrix();
}

void Transform::RotateWorldZ(const float angle)
{
	D3DXMatrixRotationZ(&mRot, angle);
	UpdateMatrix();
}

void Transform::RescaleMatrix(const D3DXVECTOR3 _vSca)
{
	vSca = _vSca;
	UpdateMatrix();
}

void Transform::TranslateMatrix(const D3DXVECTOR3 _vPos)
{
	vPos += _vPos;
	UpdateMatrix();
}

void Transform::ChangePosition(D3DXVECTOR3 _vPos) {
	vPos = _vPos;
	UpdateMatrix();
}

void Transform::SetRotation(float yaw, float pitch, float roll)
{

	D3DXMatrixIdentity(&mRot);
	D3DXQuaternionIdentity(&qRot);
	UpdateRotationFromQuaternion();
	//Rotate(yaw, pitch, roll);
	RotateYaw(yaw);
	RotatePitch(pitch);
	RotateRoll(roll);
}
