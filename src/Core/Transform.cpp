
#include "Core/Transform.h"

namespace TikiEngine
{
	Transform::Transform()
		: Position(), Rotation(), Scale(1)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Move(Vector3 direction)
	{
		this->Position += direction;
	}

	Matrix* Transform::GetWorldMatrix()
	{
		//TODO: Matrix erstellen

		//D3DXMATRIX matrix;
		//D3DXMATRIX matrixTemp;
		//D3DXMATRIX matrixTempOut;

		//D3DXMatrixIdentity(&matrix);

		//D3DXMatrixTranslation(
		//	&matrixTemp,
		//	this->Position.X,
		//	this->Position.Y,
		//	this->Position.Z
		//);
		//D3DXMatrixMultiply(&matrixTempOut, &matrix, &matrixTemp);
		//matrix = matrixTempOut;

		//D3DXMatrixScaling(
		//	&matrixTemp,
		//	this->Scale.X,
		//	this->Scale.Y,
		//	this->Scale.Z
		//);
		//D3DXMatrixMultiply(&matrixTempOut, &matrix, &matrixTemp);
		//matrix = matrixTempOut;

		//D3DXMatrixRotationX(&matrixTemp, this->Rotation.X);
		//D3DXMatrixMultiply(&matrixTempOut, &matrix, &matrixTemp);
		//matrix = matrixTempOut;

		//D3DXMatrixRotationY(&matrixTemp, this->Rotation.Y);
		//D3DXMatrixMultiply(&matrixTempOut, &matrix, &matrixTemp);
		//matrix = matrixTempOut;

		//D3DXMatrixRotationZ(&matrixTemp, this->Rotation.Z);
		//D3DXMatrixMultiply(&matrixTempOut, &matrix, &matrixTemp);
		//matrix = matrixTempOut;

		return new Matrix();
	}
}