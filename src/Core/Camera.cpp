
#include "Core/Engine.h"
#include "Core/Camera.h"

#include "Graphics/ConstantBuffer.h"

namespace TikiEngine
{
	namespace Elements
	{
		#pragma region Class
		Camera::Camera(Engine* engine)
			: Element(engine)
		{
			//D3DXMATRIX matrix;
			//D3D11_VIEWPORT* vp = engine->graphics->GetViewPort();

			//D3DXMatrixPerspectiveFovLH(
			//	&matrix,
			//	D3DX_PI / 4,
			//	(vp->Width / vp->Height),
			//	0.01f,
			//	10000.0f
			//);

			//D3DXMatrixPerspectiveOffCenterLH(
			//	&matrix,
			//	0,
			//	vp->Width,
			//	vp->Height,
			//	0,
			//	0.01f,
			//	100.0f
			//);

			//this->matrices.ProjectionMatrix = Matrix(matrix);

			//this->matrixBuffer = new ConstantBuffer<Matrices>(engine);
		}

		Camera::~Camera()
		{
			delete(matrixBuffer);
		}
		#pragma endregion

		#pragma region Member
		void Camera::Dispose()
		{
		}
		#pragma endregion

		#pragma region Member - Get/Set
		Matrices* Camera::GetMatrices()
		{
			return &matrices;
		}

		ConstantBuffer<Matrices>* Camera::GetMatrixBuffer()
		{
			return matrixBuffer;
		}

		void Camera::SetProjection(const Matrix& projection)
		{
			this->matrices.ProjectionMatrix = projection;
		}
		#pragma endregion

		#pragma region Member - Update
		void Camera::Update(const FrameArgs& args)
		{
			//D3DXMATRIX matrix;

			//g_fX += args.Input.MouseDistance.x;
			//g_fY += args.Input.MouseDistance.y;

			//D3DXVECTOR3 g_vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//D3DXVECTOR3 g_vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			//float g_fEyeDistance = 5.0f;

			//D3DXVECTOR3 g_vEye = D3DXVECTOR3(
			//	sinf(g_fX) * g_fEyeDistance,
			//	cosf(g_fY) * g_fEyeDistance,
			//	(cosf(g_fX) * sinf(g_fY)) * g_fEyeDistance
			//);

			//D3DXMatrixLookAtLH(
			//	&matrix,
			//	&g_vEye,
			//	&g_vAt,
			//	&g_vUp
			//);

			//D3DXMatrixLookAtLH(
			//	&matrix,
			//	this->PRS.Position.ToD3DXVector3(),
			//	&D3DXVECTOR3(0, 0, 0),
			//	&D3DXVECTOR3(0, 1, 0)
			//);

			//this->matrices.ViewMatrix = Matrix(matrix);

			//Matrices* data = matrixBuffer->Map();
			//data->ViewMatrix = matrices.ViewMatrix.Transpose();
			//data->ProjectionMatrix = matrices.ProjectionMatrix.Transpose();
			//matrixBuffer->Unmap();
		}
		#pragma endregion
	}
}