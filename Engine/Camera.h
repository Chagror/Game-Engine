#pragma once
class Transform;
class Camera
{
private:
	Transform* _transform;

	D3DXVECTOR3 _camRight;
	D3DXVECTOR3 _camUp;
	D3DXVECTOR3 _camForward;
	D3DXVECTOR3 _camTarget;

	D3DXVECTOR3 _currentVector;
	D3DXVECTOR3 _nextVector;

	D3DXMATRIX* _camRotationMatrix;
	D3DXMATRIX* _rotateYTmpMat;
	D3DXMATRIX* _matView;

	D3DXVECTOR3 _offset;

	float _camSpeed;

public:
	Camera();
	~Camera();
	void UpdateCamera();
	void MoveCamera();
	//void ChangeTarget();
	void ChangeTarget(D3DXVECTOR3 pos);

	Transform* GetTransform() { return _transform; }
	D3DXVECTOR3 GetCamTarget() { return _camTarget; }
	D3DXVECTOR3 GetCamForward() { return _camForward; }

	float moveLeftRight;
	float moveUpDown;
	float moveBackForward;

	bool reachDestination = false;

};

