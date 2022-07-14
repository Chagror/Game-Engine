#include "pch.h"
#include "Camera.h"
#include "Transform.h"

LPDIRECT3DDEVICE9 d3ddev;

Camera::Camera() {
	_transform = new Transform(D3DXVECTOR3(1,10,0), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	_nextVector = D3DXVECTOR3(1, 10, 0);
	_camRight = D3DXVECTOR3();
	_camUp = D3DXVECTOR3();
	_camForward = D3DXVECTOR3();
	_camTarget = D3DXVECTOR3();
	_camSpeed = 2.5f;
	_camRotationMatrix = new D3DXMATRIX();
	_rotateYTmpMat = new D3DXMATRIX();
	_matView = new D3DXMATRIX();
	_offset = D3DXVECTOR3(1, 10, 0);
}

Camera::~Camera()
{
	delete _transform;

	////delete camRight;
	//delete camUp;
	//delete camForward;
	//delete camTarget;

	delete _camRotationMatrix;
	delete _rotateYTmpMat;
	delete _matView;
}

void Camera::UpdateCamera()
{
	//Rotate Camera
	D3DXMatrixRotationYawPitchRoll(_camRotationMatrix, _transform->pitch, _transform->yaw, _transform->roll);
	D3DXVec3TransformCoord(&_camTarget, &_transform->defaultForward, _camRotationMatrix);
	D3DXMatrixRotationY(_rotateYTmpMat, _transform->yaw);

	D3DXVec3TransformCoord(&_camRight,&_transform->vRight, _rotateYTmpMat);
	D3DXVec3TransformCoord(&_camUp,&_camUp, _rotateYTmpMat);
	D3DXVec3TransformCoord(&_camForward,&_transform->defaultForward, _rotateYTmpMat);

	//Update Movement
	_transform->vPos += moveLeftRight * _camRight;
	_transform->vPos += moveBackForward * _camForward;
	_transform->vPos += moveUpDown * _transform->vUp;
	MoveCamera();

	//Reset Movement
	moveLeftRight = 0;
	moveUpDown = 0;
	moveBackForward = 0;

	_camTarget = _transform->vPos + _camTarget;

	D3DXMatrixLookAtLH(_matView,
		&_transform->vPos,    // the camera position
		&_camTarget,    // the look-at position
		&_transform->vUp);    // the up direction
	
	d3ddev->SetTransform(D3DTS_VIEW, _matView);
}

void Camera::MoveCamera() {
	D3DXVECTOR3 dir;
	dir = _nextVector - _currentVector;
	D3DXVECTOR3 diff = dir;
	D3DXVec3Normalize(&dir, &dir);

	_transform->vPos += dir * _camSpeed;
	_currentVector = _transform->vPos;
	float distance = D3DXVec3Length(&diff);
	if (distance <= 5) {
		reachDestination = true;
	}
}

void Camera::ChangeTarget(D3DXVECTOR3 pos){
	_nextVector = pos + _offset;
	reachDestination = false;
}


